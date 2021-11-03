/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:18:32 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/11/03 11:19:30 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	child1(int pipe_end[2], int fd_in, char **av_exec, char **envp)
{
	//pid_t pid;
	pid_t first_pid;
	pid_t child_getpid;
	int new_fd;

	dup2(fd_in, STDIN_FILENO);
	new_fd = dup2(pipe_end[1], STDOUT_FILENO);
	//printf("   ->child 1: zou in outfile moeten staan\n");
	close(pipe_end[0]);
	close(fd_in);
	execve("/bin/cat", av_exec, envp);
	printf("   ->dit zou niet geprint moeten worden\n");
}

void	child2(int fd_out, int pipe_end[2], char **av_exec_2, char **envp)
{
	//pid_t pid;
	pid_t first_pid;
	pid_t child_getpid;
	int new_fd;

	char *input_from_pipe;
	input_from_pipe = malloc(sizeof(char) * 1000);

	dup2(pipe_end[0], STDIN_FILENO);
	new_fd = dup2(fd_out, STDOUT_FILENO);
	close(pipe_end[1]);
	//			fprintf(stderr, "fd_out = [%d]\n", fd_out);
	//			fprintf(stderr, "fd_stout = [%d]\n", STDOUT_FILENO);
	//			fprintf(stderr, "new_fd = [%d]\n", new_fd);
	close(fd_out);
	//			read(fd_out, input_from_pipe, 1000);
	//			fprintf(stderr, "readbuffer: %s\n", input_from_pipe);
	execve("/usr/bin/wc", av_exec_2, envp);
	printf("   ->dit zou niet geprint moeten worden\n");
}

int	main(int ac, char **av, char **envp)
{
	int i;
	int	fd_in;
	int fd_out;
	int pipe_end[2];
	char **av_exec;
	char **av_exec_2;
	pid_t first_pid;
	pid_t pid_1;
	pid_t pid_2;

	pipe(pipe_end);

	av_exec = malloc(sizeof(char *) * 4);
	av_exec[0] = "cat";
	av_exec[1] = "-e";
	//av_exec[2] = av[1];
	av_exec[2] = NULL;

	av_exec_2 = malloc(sizeof(char *) * 3);
	av_exec_2[0] = "wc";
	//av_exec_2[1] = "-l";
	//av_exec_2[1] = stdin;
	av_exec_2[1] = NULL;

	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[2], O_RDWR);
	first_pid = getpid();
	printf("   ->[pid = %d]		main: getpid\n", first_pid);
	pid_1 = fork();
	if (pid_1 == 0)
		child1(pipe_end, fd_in, av_exec, envp);
	pid_2 = fork();
	if (pid_2 == 0)
		child2(fd_out, pipe_end, av_exec_2, envp);
	free(av_exec);
	first_pid = getpid();
	printf("   ->[pid = %d]		main: einde main\n", first_pid);
}