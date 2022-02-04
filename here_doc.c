/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 09:07:43 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/04 14:12:13 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include "libft/libft.h"
#include "pipex.h"

void	here_doc_handling(t_all_fd *all_fd, t_metadata *data)
{
	char	*str;

	str = NULL;
	if (!data->limiter)
		pipex_error_and_exit();
	pipe(all_fd->pipe_end);
	write (1, "> ", 2);
	get_next_line(STDIN_FILENO, &str);
	while (ft_strcmp(data->limiter, str))
	{
		write (1, "> ", 2);
		write (all_fd->pipe_end[1], str, ft_strlen(str));
		write (all_fd->pipe_end[1], "\n", 1);
		get_next_line(STDIN_FILENO, &str);
	}
	close(all_fd->pipe_end[1]);
}
