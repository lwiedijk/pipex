/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 11:40:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/25 07:52:31 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "pipex.h"
#include "libft/libft.h"

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
		i++;
	}
	free(cmd_array);
	//git try
}

void	free_on_error(char ***cmd_vectors)
{
	if (cmd_vectors)
		free_3d_array(cmd_vectors);
}

void	error_open(char *file, char ***cmd_vectors)
{
	write(STDERR_FILENO, "pipex: ", 7);
	//write(STDERR_FILENO, file, ft_strlen(file));
	//write(STDERR_FILENO, ": ", 2);
	perror(file);
	free_on_error(cmd_vectors);
	exit(EXIT_FAILURE); // exit correctly and not in error func want 2de cmd!
}

void	error_and_exit(int status, char ***cmd_vectors)
{
	if (status == USAGE)
		write(STDERR_FILENO, "usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	if (status == MALLOC_FAIL)
		write(STDERR_FILENO, "pipex: Malloc fail\n", 19);
	if (status == NO_EXISTING_PATH)
		write(STDERR_FILENO, "pipex: Non existing path entered\n", 33);
	if (status == SYS_CALL_ERR)
		perror("pipex");
	free_on_error(cmd_vectors);
	exit(EXIT_FAILURE);
}

void	close_and_check(int fd, char ***cmd_vectors)
{
	int	fail_check;

	fail_check = 0;
	fail_check = close(fd);
	if (fail_check == -1)
		error_and_exit(SYS_CALL_ERR, cmd_vectors);
}
