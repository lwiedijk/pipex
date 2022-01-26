/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 11:04:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/26 17:58:56 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h> //wait

#include <strings.h>
static void	launch_child_process(char **envp, char ***cmd_vectors, t_all_fd *all_fd,
					int child_count, int cmd_count, int previous_pipe_to_read_from)
{
	char *path;
	
	path = NULL;
	if (previous_pipe_to_read_from == 0)
	{
		if (all_fd->fd_in == -1)
			exit(1);
		if (dup2(all_fd->fd_in, STDIN_FILENO) == -1)
				error_and_exit(SYS_CALL_ERR, cmd_vectors);
	}
	else
	{
		if (dup2(previous_pipe_to_read_from, STDIN_FILENO) == -1)
			error_and_exit(SYS_CALL_ERR, cmd_vectors);
	}
	if ((child_count + 1) == cmd_count)
	{
		if (dup2(all_fd->fd_out, STDOUT_FILENO) == -1)
			error_and_exit(SYS_CALL_ERR, cmd_vectors);
	}
	else
	{
		if (dup2(all_fd->pipe_end[1], STDOUT_FILENO) == -1)
			error_and_exit(SYS_CALL_ERR, cmd_vectors);
	}
	
	//./pipex poep "cat" "ls" "cat -e" outfile

	if ((child_count + 1) != cmd_count)
		close_and_check(all_fd->pipe_end[1], cmd_vectors);
	if ((child_count + 1) != cmd_count)
		close_and_check(all_fd->pipe_end[0], cmd_vectors);
	if (previous_pipe_to_read_from != 0)
		close_and_check(previous_pipe_to_read_from, cmd_vectors);
	if (all_fd->fd_in != -1)
		close_and_check(all_fd->fd_in, cmd_vectors);
	close_and_check(all_fd->fd_out, cmd_vectors);

	//close(all_fd->pipe_end[0]);
	//close(all_fd->pipe_end[1]);


	// het is hoe dat ok incorrect dat exit impliciet word aangeroepen vanuit child!!
	// hij moet erno geven en doorgaan met volgende cmd!! 

	path = path_parser(cmd_vectors[child_count][0], envp, cmd_vectors);
	execve(path, cmd_vectors[child_count], envp);
	error_and_exit(SYS_CALL_ERR, cmd_vectors);
}

void	initialize(t_all_fd *all_fd)
{
	all_fd->fd_in = 0;
	all_fd->fd_out = 0;
	all_fd->pipe_end[0] = 0;
	all_fd->pipe_end[1] = 0;
}

void	fork_processes(t_all_fd *all_fd, char **envp, int cmd_count, char ***cmd_vectors)
{
	int		status;
	int		exitstatus = 0;
	int		child_count;
	int		previous_pipe_to_read_from;
	pid_t	wp;
	pid_t	lastpid;

	child_count = 0;
	all_fd->pipe_end[0] = 0;
	lastpid = -8;
	while (child_count < cmd_count)
	{
		previous_pipe_to_read_from = all_fd->pipe_end[0];
		if ((child_count + 1) != cmd_count)
			pipe(all_fd->pipe_end);
		lastpid = fork();
		if (lastpid == -1)
			error_and_exit(SYS_CALL_ERR, cmd_vectors);
		else if (lastpid == 0)
			launch_child_process(envp, cmd_vectors, all_fd, child_count, cmd_count, previous_pipe_to_read_from);
		close(all_fd->pipe_end[1]);
		if (previous_pipe_to_read_from != 0)
			close(previous_pipe_to_read_from);
		//fprintf(stderr, "child [%d], has PID [%d]\n", child_count, lastpid);
		child_count++;
	}
	//system("lsof -c pipex");
	while (1)
	{
		wp = waitpid(-1, &status, 0);
		//fprintf(stderr, "child with ID_[%d] closed\n", wp);
		//fprintf(stderr, "exitstatus is [%d]\n", WEXITSTATUS(status));
		if (wp == lastpid)
		{
			exitstatus = WEXITSTATUS(status);
			//fprintf(stderr, "LAST_exitstatus is [%d]\n", exitstatus);
			//fprintf(stderr, "LAST_wp is [%d]\n", wp);
		}
		else if (wp == -1)
			break ;
	}
}
