/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_process_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:31:35 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/04 14:10:01 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"
#include "get_next_line.h"

static void	redirect_fd(t_all_fd *all_fd, t_metadata *data)
{
	if (all_fd->previous_read_end == 0)
	{
		if (all_fd->fd_in == -1)
			exit(EXIT_FAILURE);
		if (dup2(all_fd->fd_in, STDIN_FILENO) == -1)
			error_message_and_exit();
	}
	else
	{
		if (dup2(all_fd->previous_read_end, STDIN_FILENO) == -1)
			error_message_and_exit();
	}
	if ((data->child_count + 1) == data->cmd_count)
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
}

static void	close_unused_fd(t_all_fd *all_fd, t_metadata *data)
{
	if ((data->child_count + 1) != data->cmd_count)
		close_and_check(all_fd->pipe_end[1]);
	if ((data->child_count + 1) != data->cmd_count)
		close_and_check(all_fd->pipe_end[0]);
	if (all_fd->previous_read_end != 0)
		close_and_check(all_fd->previous_read_end);
	if (all_fd->fd_in != -1)
		close_and_check(all_fd->fd_in);
	if (all_fd->fd_out != -1)
		close_and_check(all_fd->fd_out);
}

void	execute_cmd(t_metadata *data, t_all_fd *all_fd,
			char **envp, char ***cmd_vectors)
{
	char	*path;

	path = NULL;
	redirect_fd(all_fd, data);
	close_unused_fd(all_fd, data);
	path = path_parser(cmd_vectors[data->child_count][0], envp);
	execve(path, cmd_vectors[data->child_count], envp);
	error_message_and_exit();
}
