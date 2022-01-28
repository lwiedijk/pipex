/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 11:40:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/28 13:26:13 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "pipex.h"
#include "libft/libft.h"

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_3d_array(char ***cmd_array)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_array[i])
	{
		j = 0;
		while (cmd_array[i][j])
		{
			free(cmd_array[i][j]);
			j++;
		}
		free(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}

void	command_not_found(char *error_object)
{
	if (write(STDERR_FILENO, "pipex: ", 7) == -1)
		error_message_and_exit();
	if (write(STDERR_FILENO, error_object, ft_strlen(error_object)) == -1)
		error_message_and_exit();
	if (write(STDERR_FILENO, ": command not found\n", 20) == -1)
		error_message_and_exit();
	exit(127);
}

void	error_message_and_continue(char *error_object)
{
	if (write(STDERR_FILENO, "pipex: ", 7) == -1)
		error_message_and_exit();
	perror(error_object);
}

void	error_message_and_exit(void)
{
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	pipex_error_and_exit(void)
{
	if (write(STDERR_FILENO, "usage: ./pipex file1 cmd1 cmd2 file2\n", 37) == -1)
		error_message_and_exit();
	exit(EXIT_FAILURE);
}

void	close_and_check(int fd)
{
	int	fail_check;

	fail_check = 0;
	fail_check = close(fd);
	if (fail_check == -1)
		error_message_and_continue("fd");
}
