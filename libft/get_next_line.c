/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 12:17:00 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/08 08:54:00 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*get_remainder(char *remainder, char **newline)
{
	char	*line;

	*newline = NULL;
	*newline = ft_strchr(remainder, '\n');
	if (*newline)
	{
		**newline = '\0';
		line = ft_strdup(remainder);
		if (!line)
			return (NULL);
		(*newline)++;
		ft_strlcpy(remainder, *newline, (ft_strlen(*newline) + 1));
	}
	else
	{
		line = ft_strdup(remainder);
		if (!line)
			return (NULL);
		ft_bzero(remainder, ft_strlen(remainder));
	}
	return (line);
}

static int	ft_read(char **buf, int *bytes_read, int fd)
{
	*buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (*buf == NULL)
		return (-1);
	*bytes_read = read(fd, *buf, BUFFER_SIZE);
	if (*bytes_read < 0)
		return (-1);
	return (0);
}

static void	check_newline(char **newline, char *buf, char *remainder)
{
	*newline = NULL;
	*newline = ft_strchr(buf, '\n');
	if (*newline)
	{
		**newline = '\0';
		*newline = *newline + 1;
		ft_strlcpy(remainder, *newline, (ft_strlen(*newline) + 1));
	}
}

static int	return_gnl(int bytes_read)
{
	if (bytes_read)
		return (1);
	else
		return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	remainder[BUFFER_SIZE + 1];
	char		*buf;
	int			bytes_read;
	char		*newline;

	if (!line || fd < 0 || read(fd, remainder, 0) || BUFFER_SIZE < 1)
		return (-1);
	*line = NULL;
	bytes_read = 1;
	*line = get_remainder(remainder, &newline);
	if (*line == NULL)
		return (-1);
	while (!newline && bytes_read)
	{
		if (ft_read(&buf, &bytes_read, fd))
			return (-1);
		buf[bytes_read] = '\0';
		check_newline(&newline, buf, remainder);
		*line = ft_strjoin_free(*line, buf);
		if (*line == NULL)
			return (-1);
		free(buf);
	}
	return (return_gnl(bytes_read));
}
