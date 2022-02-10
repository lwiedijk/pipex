/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 11:40:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/10 13:53:06 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "pipex.h"

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

void	pipex_usage_error(void)
{
	char	*str;

	str = "pipex: usage: ./pipex file1 cmd1 cmd2 file2\n";
	if (write(STDERR_FILENO, str, ft_strlen(str)) == -1)
		error_message_and_exit();
	exit(EXIT_FAILURE);
}

void	pipex_bonus_usage_error(int error_code)
{
	char	*bonus;
	char	*heredoc;

	bonus = "pipex: bonus-usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n";
	heredoc = "pipex: heredoc-usage: ./pipex here_doc LIMITER cmd1 cmd2 file\n";
	if (error_code == BONUS)
	{
		if (write(STDERR_FILENO, bonus, ft_strlen(bonus)) == -1)
			error_message_and_exit();
	}
	if (error_code == HEREDOC)
	{
		if (write(STDERR_FILENO, heredoc, ft_strlen(heredoc)) == -1)
			error_message_and_exit();
	}
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
