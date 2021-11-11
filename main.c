/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:18:32 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/11/11 10:52:05 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //ook voor macro's voor access
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "pipex.h"
#include "libft/libft.h"

void	error_and_exit(int status)
{
	if (status == USAGE)
	{
		write(STDERR_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
		exit(EXIT_FAILURE);
	}
}

void	free_2d_array(char **cmd_array)
{
	int i;

	i = 0;
	while (cmd_array[i])
	{
		free(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}

char	*path_parser(char *cmd, char **envp)
{
	char *path;
	char **env_path;
	char **temp;
	int count;
	int i;
	int j;
	int read_access;

	i = 0;
	count = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A')
		{
			printf("envp in path_parser = [%s]\n", envp[i]);
			temp = ft_split(envp[i], '=');
			printf("temp_path[1] = [%s]\n", temp[1]);
			env_path = ft_split_and_count(temp[1], ':', &count);
			free_2d_array(temp);
			break ;
		}
		i++;
	}
	j = 0;
	while(j < count)
	{
		printf("path[%d] = [%s]\n", j, env_path[j]);
		j++;
	}
	i = 0;
	while (i < count)
	{
		path = ft_strjoin("/", cmd);
		printf("path = [%s]\n", path);
		path = ft_strjoin_free(env_path[i], path);
		printf("path = [%s]\n", path);
		read_access = access(path, F_OK | X_OK);
		printf("access_%d returned [%d]\n", i, read_access);
		if (read_access != 0)
			free(path);
		else
			break ;
		i++;
	}
	printf("return path = [%s]\n", path);
	return (path);
}

void	child1(int pipe_end[2], int fd_in, char **av_exec, char **envp)
{
	char *path;

	path = path_parser(av_exec[0], envp);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit(1);
	if (dup2(pipe_end[1], STDOUT_FILENO) == -1)
		exit(1);
	close(pipe_end[0]); //fd unuseds in child1
	close (pipe_end[1]); //fd no longer needed in child sindse stdOUT is a copy of this 
	close(fd_in); //fd no longer needed in child sindse stdIN is a copy of this 
	execve(path, av_exec, envp);
	exit(1); //it only gets to this live in case exec fails. 
}

void	child2(int fd_out, int pipe_end[2], char **av_exec_2, char **envp)
{ 
	//char *input_from_pipe;
	//input_from_pipe = malloc(sizeof(char) * 1000);
	char *path;
	path = path_parser(av_exec_2[0], envp);

	if (dup2(pipe_end[0], STDIN_FILENO) == -1)
		exit(1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(1);
	close(pipe_end[1]); //fd unuseds in child2
	close(pipe_end[0]); //fd no longer needed in child sindse stdIN is a copy of this 
	close(fd_out); //fd no longer needed in child sindse stdOUT is a copy of this 
	execve(path, av_exec_2, envp);
	exit(1); //it only gets to this live in case exec fails. 
}

int	main(int ac, char **av, char **envp)
{
	int	fd_in;
	int fd_out;
	int pipe_end[2];
	char **av_exec;
	char **av_exec_2;
	pid_t pid_1;
	pid_t pid_2;
	int i;
	int count;
	int count2;
	
	if (ac != 5)
		error_and_exit(USAGE);
	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A')
			printf("envp = [%s]\n", envp[i]);
		i++;
	}
	count = 0;
	av_exec = ft_split_and_count(av[2], ' ', &count);
	av_exec_2 = ft_split_and_count(av[3], ' ', &count2);
	pipe(pipe_end);
	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[4], O_CREAT | O_RDWR | O_TRUNC, MODE_RW_R_R);
	if (fd_in < 0 || fd_out < 0)
	{
		perror("Error");
		exit (EXIT_FAILURE);
	}
	pid_1 = fork();
	//perror("Fork: ");
	if (pid_1 == 0)
	{
		close(fd_out); //fd unuseds in child1
		child1(pipe_end, fd_in, av_exec, envp);
	}
	pid_2 = fork();
	if (pid_2 == 0)
	{
		close(fd_in); //fd unuseds in child2
		child2(fd_out, pipe_end, av_exec_2, envp);
	}
	free_2d_array(av_exec);
	free_2d_array(av_exec_2);
	//system("leaks pipex");

	//pipex(fd1, fd2, av, envp);
}
