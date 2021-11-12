/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:18:32 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/11/12 09:08:54 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //ook voor macro's voor access
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "pipex.h"
#include "libft/libft.h"

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

void	free_on_error(t_exec_vectors *exec_vectors)
{
	if (exec_vectors->vector1)
		free_2d_array(exec_vectors->vector1);
	else if (exec_vectors->vector2)
		free_2d_array(exec_vectors->vector2);
}

void	error_and_exit(int status, t_exec_vectors *exec_vectors)
{
	if (status == USAGE)
		write(STDERR_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	if (status == MALLOC_FAIL)
		write(STDERR_FILENO, "Pipex: Malloc fail\n", 19);
	if (status == SYS_CALL_ERR)
		perror("");
	free_on_error(exec_vectors);
	exit(EXIT_FAILURE);
}

void	close_and_check(int fd, t_exec_vectors *exec_vectors)
{
	int fail_check;

	fail_check = 0;
	fail_check = close(fd);
	if (fail_check == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
}

char	*path_parser(char *cmd, char **envp, t_exec_vectors *exec_vectors)
{
	char *path;
	char **env_path;
	char **temp;
	int count;
	int i;
	int read_access;

	i = 0;
	count = 0;
	read_access = 0;
	temp = NULL;
	env_path = NULL;
	path = NULL;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A')
		{
			temp = ft_split(envp[i], '=');
			if (!temp)
				error_and_exit(MALLOC_FAIL, &exec_vectors);
			env_path = ft_split_and_count(temp[1], ':', &count);
			if (!env_path)
				error_and_exit(MALLOC_FAIL, &exec_vectors);
			free_2d_array(temp);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < count)
	{
		path = ft_strjoin("/", cmd);
		if (!path)
			error_and_exit(MALLOC_FAIL, &exec_vectors);
		path = ft_strjoin_free(env_path[i], path);
		if (!path)
			error_and_exit(MALLOC_FAIL, &exec_vectors);
		read_access = access(path, F_OK | X_OK);
		if (read_access != 0)
			free(path);
		else
			break ;
		i++;
	}
	return (path);
}

void	child1(int pipe_end[2], int fd_in, char **envp, t_exec_vectors *exec_vectors)
{
	char *path;

	path = path_parser(exec_vectors->vector1[0], envp, exec_vectors);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
	if (dup2(pipe_end[1], STDOUT_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
	close_and_check(pipe_end[0], exec_vectors); //fd unuseds in child1
	close_and_check(pipe_end[1], exec_vectors); //fd no longer needed in child sindse stdOUT is a copy of this 
	close_and_check(fd_in, exec_vectors); //fd no longer needed in child sindse stdIN is a copy of this 
	execve(path, exec_vectors->vector1, envp);
	error_and_exit(SYS_CALL_ERR, exec_vectors); //it only gets to this live in case exec fails. 
}

void	child2(int fd_out, int pipe_end[2], char **envp, t_exec_vectors *exec_vectors)
{ 
	char *path;
	
	path = path_parser(exec_vectors->vector2[0], envp, exec_vectors);
	if (dup2(pipe_end[0], STDIN_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
	close_and_check(pipe_end[1], exec_vectors); //fd unuseds in child2
	close_and_check(pipe_end[0], exec_vectors); //fd no longer needed in child sindse stdIN is a copy of this 
	close_and_check(fd_out, exec_vectors); //fd no longer needed in child sindse stdOUT is a copy of this 
	execve(path, exec_vectors->vector2, envp);
	error_and_exit(SYS_CALL_ERR, exec_vectors); //it only gets to this live in case exec fails. 
}

void	initialize(t_exec_vectors *exec_vectors, t_all_fd *all_fd)
{
	exec_vectors->vector1 = NULL;
	exec_vectors->vector2 = NULL;
	all_fd->fd_in = 0;
	all_fd->fd_out = 0;
	all_fd->pipe_end[0] = 0;
	all_fd->pipe_end[1] = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_exec_vectors	exec_vectors;
	t_all_fd		all_fd;
	pid_t pid_1;
	pid_t pid_2;
	int count;
	int count2;

	initialize(&exec_vectors, &all_fd);

	if (ac != 5)
		error_and_exit(USAGE, &exec_vectors);
	count = 0;
	exec_vectors.vector1 = ft_split_and_count(av[2], ' ', &count);
	if (!exec_vectors.vector1)
		error_and_exit(MALLOC_FAIL, &exec_vectors);
	exec_vectors.vector2 = ft_split_and_count(av[3], ' ', &count2);
	if (!exec_vectors.vector2)
		error_and_exit(MALLOC_FAIL, &exec_vectors);
	if (pipe(all_fd.pipe_end) == -1)
		error_and_exit(SYS_CALL_ERR, &exec_vectors);
	all_fd.fd_in = open(av[1], O_RDONLY);
	all_fd.fd_out = open(av[4], O_CREAT | O_RDWR | O_TRUNC, MODE_RW_R_R);
	if (all_fd.fd_in < 0 || all_fd.fd_out < 0)
		error_and_exit(SYS_CALL_ERR, &exec_vectors);
	pid_1 = fork();
	if (pid_1 == -1)
		error_and_exit(SYS_CALL_ERR, &exec_vectors);
	if (pid_1 == 0)
	{
		close_and_check(all_fd.fd_out, &exec_vectors); //fd unuseds in child1
		child1(all_fd.pipe_end, all_fd.fd_in, envp, &exec_vectors);
	}
	pid_2 = fork();
	if (pid_2 == -1)
		error_and_exit(SYS_CALL_ERR, &exec_vectors);
	if (pid_2 == 0)
	{
		close_and_check(all_fd.fd_in, &exec_vectors); //fd unuseds in child2
		child2(all_fd.fd_out, all_fd.pipe_end, envp, &exec_vectors);
	}
	free_2d_array(exec_vectors.vector1);
	free_2d_array(exec_vectors.vector2);
	//system("leaks pipex");

	//pipex(fd1, fd2, av, envp);
}
