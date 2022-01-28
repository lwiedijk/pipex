/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/28 13:55:45 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/28 14:09:32 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "pipex.h"

void	close_and_check(int fd)
{
	int	fail_check;

	fail_check = 0;
	fail_check = close(fd);
	if (fail_check == -1)
		error_message_and_continue("fd");
}

bool	is_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

void	initialize(t_all_fd *all_fd)
{
	all_fd->fd_in = 0;
	all_fd->fd_out = 0;
	all_fd->pipe_end[0] = 0;
	all_fd->pipe_end[1] = 0;
	all_fd->exitstatus = 0;
}
