/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 11:04:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/28 13:00:50 by lwiedijk      ########   odam.nl         */
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
			exit(EXIT_FAILURE);
		if (dup2(all_fd->fd_in, STDIN_FILENO) == -1)
				error_message_and_exit();
	}
	else
	{
		if (dup2(previous_pipe_to_read_from, STDIN_FILENO) == -1)
			error_message_and_exit();
	}
	if ((child_count + 1) == cmd_count)
	{
		if (all_fd->fd_out == -1)
			exit(EXIT_FAILURE);
		if (dup2(all_fd->fd_out, STDOUT_FILENO) == -1)
			error_message_and_exit();
	}
	else
	{
		if (dup2(all_fd->pipe_end[1], STDOUT_FILENO) == -1)
			error_message_and_exit();
	}
	
	//./pipex poep "env" "ls" "cat -e" outfile

	//./pipex infile.txt "env" "ls" "hoi" outfile
	//< infile.txt env | ls | hoi > outfile_term

	if ((child_count + 1) != cmd_count)
		close_and_check(all_fd->pipe_end[1]);
	if ((child_count + 1) != cmd_count)
		close_and_check(all_fd->pipe_end[0]);
	if (previous_pipe_to_read_from != 0)
		close_and_check(previous_pipe_to_read_from);
	if (all_fd->fd_in != -1)
		close_and_check(all_fd->fd_in);
	if (all_fd->fd_out != -1)
		close_and_check(all_fd->fd_out);

	path = path_parser(cmd_vectors[child_count][0], envp);
	execve(path, cmd_vectors[child_count], envp);
	error_message_and_exit();
}

void	initialize(t_all_fd *all_fd)
{
	all_fd->fd_in = 0;
	all_fd->fd_out = 0;
	all_fd->pipe_end[0] = 0;
	all_fd->pipe_end[1] = 0;
	all_fd->exitstatus = 0;
}

void	fork_processes(t_all_fd *all_fd, char **envp, int cmd_count, char ***cmd_vectors)
{
	int		status;
	int		child_count;
	int		previous_pipe_to_read_from;
	pid_t	wp;
	pid_t	lastpid;

	child_count = 0;
	lastpid = 0;
	while (child_count < cmd_count)
	{
		previous_pipe_to_read_from = all_fd->pipe_end[0];
		if ((child_count + 1) != cmd_count)
		{
			if(pipe(all_fd->pipe_end) == -1)
				error_message_and_exit();
		}
		lastpid = fork();
		if (lastpid == -1)
			error_message_and_exit();
		else if (lastpid == 0)
			launch_child_process(envp, cmd_vectors, all_fd, child_count, cmd_count, previous_pipe_to_read_from);
		if ((child_count + 1) != cmd_count)
			close_and_check(all_fd->pipe_end[1]);
		if (previous_pipe_to_read_from != 0)
			close_and_check(previous_pipe_to_read_from);
		child_count++;
	}
	close_and_check(all_fd->fd_in);
	close_and_check(all_fd->fd_out);
	//system("lsof -c pipex");
	while (1)
	{
		wp = waitpid(-1, &status, 0);
		if (wp == lastpid)
		{
			all_fd->exitstatus = WEXITSTATUS(status);
			fprintf(stderr, "exitstatus of lastpid = [%d]\n", all_fd->exitstatus);
		}
		else if (wp == -1)
			break ;
	}
}
