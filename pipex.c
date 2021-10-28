/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 11:04:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/10/28 09:40:52 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> //perror
#include <fcntl.h> //O_RDONLY macro's

void	pipex(int fd1, int fd2, char **av, char *envp[])
{
	int		pipe_end[2];
	pid_t	parent_pid;

	pipe(pipe_end);
	parent_pid = -1;//fork();
	if (parent_pid < 0)
	{
		perror("Fork");
		//return (EXIT_FAILURE);
	}
	//if (!parent_pid) //when returnes 0 we are in child process
	//	child_process(fd1, cmd1);
	//else
	//	parent_process(fd2, cmd2);
}

int	main(int ac, char **av, char *envp[])
{
	int fd1;
	int fd2;

	//perror("Fork: ");
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	printf("fd1 = [%d]\n", fd1);
	printf("fd2 = [%d]\n", fd2);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("Error");
		//return (-1);
	}
	pipex(fd1, fd2, av, envp);
	return (-1);
	
	//int i;
	//
	//i = 0;
	//while (envp[i])
	//{
	//	printf("envp = [%s]\n", envp[i]);
	//	i++;
	//}
}
