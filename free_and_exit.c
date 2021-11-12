/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 11:40:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/11/12 11:42:39 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "pipex.h"

void	free_2d_array(char **cmd_array)
{
	int	i;

	i = 0;
	while (cmd_array[i])
	{
		free(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}

void	free_on_error(t_exec_vectors *exec_vectors)
{
	if (exec_vectors->vector1)
		free_2d_array(exec_vectors->vector1);
	else if (exec_vectors->vector2)
		free_2d_array(exec_vectors->vector2);
}

void	error_and_exit(int status, t_exec_vectors *exec_vectors)
{
	if (status == USAGE)
		write(STDERR_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	if (status == MALLOC_FAIL)
		write(STDERR_FILENO, "Pipex: Malloc fail\n", 19);
	if (status == SYS_CALL_ERR)
		perror("");
	free_on_error(exec_vectors);
	exit(EXIT_FAILURE);
}

void	close_and_check(int fd, t_exec_vectors *exec_vectors)
{
	int	fail_check;

	fail_check = 0;
	fail_check = close(fd);
	if (fail_check == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
}
