/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 11:33:23 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/09 11:20:12 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

char	***argument_parser(char **av, int cmd_count, t_metadata *data)
{
	int		i;
	int		j;
	int		unused_arg_vals;
	char	***vector;

	i = 0;
	unused_arg_vals = INFILE_EXECPATH;
	if (data->limiter)
	{
		data->cmd_count = data->cmd_count - 1;
		unused_arg_vals = INFILE_EXECPATH + 1;
	}
	vector = (char ***)malloc(sizeof(char **) * (cmd_count + 1));
	if (!vector)
		error_message_and_exit();
	vector[cmd_count] = NULL;
	while (i < cmd_count)
	{
		j = (i + unused_arg_vals);
		vector[i] = ft_split(av[j], ' ');
		if (!vector[i])
			error_message_and_exit();
		i++;
	}
	return (vector);
}

static char	*check_path(char *cmd, char **env_path, int count)
{
	char	*path;
	int		i;
	int		is_not_executable;

	path = NULL;
	i = 0;
	while (i < count)
	{
		path = ft_strjoin("/", cmd);
		if (!path)
			error_message_and_exit();
		path = ft_strjoin_free(env_path[i], path);
		if (!path)
			error_message_and_exit();
		is_not_executable = access(path, F_OK | X_OK);
		if (is_not_executable)
		{
			free(path);
			path = NULL;
		}
		else
			break ;
		i++;
	}
	return (path);
}

static char	*check_absolute_path(char *path)
{
	int	is_not_executable;
	int	file_does_not_exist;

	if (!is_path(path))
		command_not_found(path);
	is_not_executable = access(path, F_OK | X_OK);
	if (is_not_executable)
	{
		file_does_not_exist = access(path, F_OK);
		if (file_does_not_exist)
		{
			error_message_and_continue(path);
			exit(127);
		}
		else
		{
			error_message_and_continue(path);
			exit(126);
		}
	}
	return (path);
}

static char	**get_env_path_array(char **envp, int *count)
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
				error_message_and_exit();
			env_path = ft_split_and_count(temp[1], ':', count);
			if (!env_path)
				error_message_and_exit();
			free_2d_array(temp);
			break ;
		}
		i++;
	}
	return (env_path);
}

char	*path_parser(char *cmd, char **envp)
{
	char	*path;
	char	**env_path;
	int		count;

	count = 0;
	path = NULL;
	env_path = get_env_path_array(envp, &count);
	path = check_path(cmd, env_path, count);
	if (!path)
		path = check_absolute_path(cmd);
	return (path);
}
