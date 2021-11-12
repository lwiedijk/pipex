/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 11:33:23 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/11/12 11:48:18 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "pipex.h"

void	argument_parser(t_exec_vectors *exec_vectors, char **av)
{
	exec_vectors->vector1 = ft_split(av[2], ' ');
	if (!exec_vectors->vector1)
		error_and_exit(MALLOC_FAIL, exec_vectors);
	exec_vectors->vector2 = ft_split(av[3], ' ');
	if (!exec_vectors->vector2)
		error_and_exit(MALLOC_FAIL, exec_vectors);
}

static char	*check_path(char *cmd, char **env_path, int count,
			t_exec_vectors *exec_vectors)
{
	char	*path;
	int		i;
	int		read_access;

	i = 0;
	while (i < count)
	{
		path = ft_strjoin("/", cmd);
		if (!path)
			error_and_exit(MALLOC_FAIL, exec_vectors);
		path = ft_strjoin_free(env_path[i], path);
		if (!path)
			error_and_exit(MALLOC_FAIL, exec_vectors);
		read_access = access(path, F_OK | X_OK);
		if (read_access != 0)
			free(path);
		else
			break ;
		i++;
	}
	return (path);
}

static char	**get_path_array(t_exec_vectors *exec_vectors,
			char **envp, int *count)
{
	char	**env_path;
	char	**temp;
	int		i;

	i = 0;
	temp = NULL;
	env_path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			temp = ft_split(envp[i], '=');
			if (!temp)
				error_and_exit(MALLOC_FAIL, exec_vectors);
			env_path = ft_split_and_count(temp[1], ':', count);
			if (!env_path)
				error_and_exit(MALLOC_FAIL, exec_vectors);
			free_2d_array(temp);
			break ;
		}
		i++;
	}
	return (env_path);
}

char	*path_parser(char *cmd, char **envp, t_exec_vectors *exec_vectors)
{
	char	*path;
	char	**env_path;
	int		count;

	count = 0;
	path = NULL;
	env_path = get_path_array(exec_vectors, envp, &count);
	path = check_path(cmd, env_path, count, exec_vectors);
	return (path);
}
