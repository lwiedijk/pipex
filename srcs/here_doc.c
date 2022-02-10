/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 09:07:43 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/10 14:01:06 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "pipex.h"

static char	*get_input(char *str)
{
	write (STDOUT_FILENO, "> ", 2);
	if (get_next_line(STDIN_FILENO, &str) == -1)
		error_message_and_exit();
	return (str);
}

void	here_doc_handling(t_all_fd *all_fd, t_metadata *data)
{
	char	*str;
	char	*temp;

	str = NULL;
	if (!data->limiter)
		pipex_bonus_usage_error(HEREDOC);
	pipe(all_fd->pipe_end);
	str = get_input(str);
	while (ft_strcmp(data->limiter, str))
	{
		temp = ft_strjoin(str, "\n");
		if (!temp)
			error_message_and_exit();
		write (all_fd->pipe_end[1], temp, ft_strlen(temp));
		free(str);
		free(temp);
		str = get_input(str);
	}
	free(str);
	close(all_fd->pipe_end[1]);
}
