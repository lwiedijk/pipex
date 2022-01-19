/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 11:33:23 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/18 17:43:07 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "pipex.h"
#include <stdio.h>

char	***argument_parser(t_exec_vectors *exec_vectors, char **av, int ac)
{
	int i = 0;
	int j; // minus de executavle naam en de infile
	char	***vector;

	vector = (char ***)malloc(sizeof(char **) * (ac + 1));
	vector[ac] = NULL;
	while(i < ac)
	{
		j = (i + 2);
		vector[i] = ft_split(av[j], ' ');
		i++;
	}
	//fprintf(stderr, "3D_array_vector = %s\n", vector[0][0]);
	//fprintf(stderr, "3D_array_vector = %s\n", vector[0][1]);
	//fprintf(stderr, "3D_array_vector = %s\n", vector[0][2]);
//
	//fprintf(stderr, "3D_array_vector = %s\n", vector[1][0]);
	//fprintf(stderr, "3D_array_vector = %s\n", vector[1][1]);
	//fprintf(stderr, "3D_array_vector = %s\n", vector[1][2]);

	exec_vectors->vector1 = ft_split(av[2], ' ');
	if (!exec_vectors->vector1)
		error_and_exit(MALLOC_FAIL, exec_vectors);
	exec_vectors->vector2 = ft_split(av[3], ' ');
	if (!exec_vectors->vector2)
		error_and_exit(MALLOC_FAIL, exec_vectors);
	return(vector);
}

static char	*check_path(char *cmd, char **env_path, int count,
			t_exec_vectors *exec_vectors)
{
	char	*path;
	int		i;
	int		read_access;
	int		read_access_2;

	i = 0;
	while (i < count)
	{
		printf("check_path: cmd is [%s]\n", cmd);
		path = ft_strjoin("/", cmd);
		if (!path)
			error_and_exit(MALLOC_FAIL, exec_vectors);
		path = ft_strjoin_free(env_path[i], path);
		if (!path)
			error_and_exit(MALLOC_FAIL, exec_vectors);
		read_access_2 = access(cmd, F_OK | X_OK);
		read_access = access(path, F_OK | X_OK);
		//fprintf(stderr, "check_path: path is [%s]\n", path);
		//fprintf(stderr, "check_path: access_status_2 is [%d]\n", read_access_2);
		if (read_access != 0)
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
	//fprintf(stderr, "check\n");
	env_path = get_path_array(exec_vectors, envp, &count);
	path = check_path(cmd, env_path, count, exec_vectors);
	fprintf(stderr, "path_parser: path is [%s]\n", path);
	//path = NULL;
	if (!path)
		exit(120);//error_and_exit(NO_EXISTING_PATH, exec_vectors);
	return (path);
}
