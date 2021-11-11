/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:18:32 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/11/11 15:21:16 by lwiedijk      ########   odam.nl         */
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
		write(STDERR_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	if (status == MALLOC_FAIL)
		write(STDERR_FILENO, "Pipex: Malloc fail\n", 19);
	if (status == SYS_CALL_ERR)
		perror("");
	exit(EXIT_FAILURE);
}

void	close_and_check(int fd)
{
	int fail_check;

	fail_check = 0;
	fail_check = close(fd);
	if (fail_check == -1)
		error_and_exit(SYS_CALL_ERR);
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
	int read_access;

	i = 0;
	count = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A')
		{
			temp = ft_split(envp[i], '=');
			env_path = ft_split_and_count(temp[1], ':', &count);
			free_2d_array(temp);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < count)
	{
		path = ft_strjoin("/", cmd);
		path = ft_strjoin_free(env_path[i], path);
		read_access = access(path, F_OK | X_OK);
		if (read_access != 0)
			free(path);
		else
			break ;
		i++;
	}
	return (path);
}

void	child1(int pipe_end[2], int fd_in, char **av_exec, char **envp)
{
	char *path;

	path = path_parser(av_exec[0], envp);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR);
	if (dup2(pipe_end[1], STDOUT_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR);
	close_and_check(pipe_end[0]); //fd unuseds in child1
	close_and_check(pipe_end[1]); //fd no longer needed in child sindse stdOUT is a copy of this 
	close_and_check(fd_in); //fd no longer needed in child sindse stdIN is a copy of this 
	execve(path, av_exec, envp);
	error_and_exit(SYS_CALL_ERR); //it only gets to this live in case exec fails. 
}

void	child2(int fd_out, int pipe_end[2], char **av_exec_2, char **envp)
{ 
	char *path;
	path = path_parser(av_exec_2[0], envp);

	if (dup2(pipe_end[0], STDIN_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR);
	close_and_check(pipe_end[1]); //fd unuseds in child2
	close_and_check(pipe_end[0]); //fd no longer needed in child sindse stdIN is a copy of this 
	close_and_check(fd_out); //fd no longer needed in child sindse stdOUT is a copy of this 
	execve(path, av_exec_2, envp);
	error_and_exit(SYS_CALL_ERR); //it only gets to this live in case exec fails. 
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
		error_and_exit(USAGE);
	count = 0;
	exec_vectors.vector1 = ft_split_and_count(av[2], ' ', &count);
	if (!exec_vectors.vector1)
		error_and_exit(MALLOC_FAIL);
	exec_vectors.vector2 = ft_split_and_count(av[3], ' ', &count2);
	if (!exec_vectors.vector2)
		error_and_exit(MALLOC_FAIL);
	if (pipe(all_fd.pipe_end) == -1)
		error_and_exit(SYS_CALL_ERR);
	all_fd.fd_in = open(av[1], O_RDONLY);
	all_fd.fd_out = open(av[4], O_CREAT | O_RDWR | O_TRUNC, MODE_RW_R_R);
	if (all_fd.fd_in < 0 || all_fd.fd_out < 0)
		error_and_exit(SYS_CALL_ERR);
	pid_1 = fork();
	if (pid_1 == -1)
		error_and_exit(SYS_CALL_ERR);
	if (pid_1 == 0)
	{
		close_and_check(all_fd.fd_out); //fd unuseds in child1
		child1(all_fd.pipe_end, all_fd.fd_in, exec_vectors.vector1, envp);
	}
	pid_2 = fork();
	if (pid_2 == -1)
		error_and_exit(SYS_CALL_ERR);
	if (pid_2 == 0)
	{
		close_and_check(all_fd.fd_in); //fd unuseds in child2
		child2(all_fd.fd_out, all_fd.pipe_end, exec_vectors.vector2, envp);
	}
	free_2d_array(exec_vectors.vector1);
	free_2d_array(exec_vectors.vector2);
	//system("leaks pipex");

	//pipex(fd1, fd2, av, envp);
}
