/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 11:40:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/08 09:32:43 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

void	error_message_and_exit(void)
{
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	error_message_and_continue(char *error_object)
{
	if (write(STDERR_FILENO, "pipex: ", 7) == -1)
		error_message_and_exit();
	perror(error_object);
}

void	pipex_error_and_exit(void)
{
	if (write(STDERR_FILENO, "pipex: ", 7) == -1)
		error_message_and_exit();
	if (write(STDERR_FILENO, "usage: ./pipex file1 cmd1 cmd2 file2\n", 37) == -1)
		error_message_and_exit();
	exit(EXIT_FAILURE);
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
