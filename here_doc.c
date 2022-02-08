/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 09:07:43 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/08 14:44:55 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "pipex.h"

static char	*get_input(char *str)
{
	write (STDOUT_FILENO, "> ", 2);
	get_next_line(STDIN_FILENO, &str);
	return (str);
}

void	here_doc_handling(t_all_fd *all_fd, t_metadata *data)
{
	char	*str;

	str = NULL;
	if (!data->limiter)
		pipex_error_and_exit();
	pipe(all_fd->pipe_end);
	str = get_input(str);
	while (ft_strcmp(data->limiter, str))
	{
		str = ft_strjoin(str, "\n");
		if (!str)
			error_message_and_exit();
		write (all_fd->pipe_end[1], str, ft_strlen(str));
		free(str);
		str = get_input(str);
	}
	close(all_fd->pipe_end[1]);
}
