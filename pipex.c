/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 11:04:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/04 14:25:37 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"

static void	fork_processes(t_metadata *data, t_all_fd *all_fd,
			char **envp, char ***cmd_vectors)
{
	while (data->child_count < data->cmd_count)
	{
		all_fd->previous_read_end = all_fd->pipe_end[0];
		if ((data->child_count + 1) != data->cmd_count)
		{
			if (pipe(all_fd->pipe_end) == -1)
				error_message_and_exit();
		}
		data->lastpid = fork();
		if (data->lastpid == -1)
			error_message_and_exit();
		else if (data->lastpid == 0)
			execute_cmd(data, all_fd, envp, cmd_vectors);
		if ((data->child_count + 1) != data->cmd_count)
			close_and_check(all_fd->pipe_end[1]);
		if (all_fd->previous_read_end != 0)
			close_and_check(all_fd->previous_read_end);
		data->child_count++;
	}
	if (all_fd->fd_in != -1)
		close_and_check(all_fd->fd_in);
	if (all_fd->fd_out != -1)
		close_and_check(all_fd->fd_out);
}

void	pipex(t_metadata *data, t_all_fd *all_fd,
			char **envp, char ***cmd_vectors)
{
	int		status;
	pid_t	wp;

	fork_processes(data, all_fd, envp, cmd_vectors);
	while (1)
	{
		wp = waitpid(-1, &status, 0);
		if (wp == data->lastpid)
			data->exitstatus = WEXITSTATUS(status);
		else if (wp == -1)
			break ;
	}
}
