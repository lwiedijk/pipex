/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   infile_to_cmd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 11:27:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/11/02 13:18:00 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	child1(int pipe_end, char **av_exec, char **envp)
{
	pid_t pid;
	pid_t first_pid;
	pid_t child_getpid;
	int new_fd;

	pid = fork();
	printf("   ->[pid = %d]		child1: pid als returen van fork in child1\n", pid);
	if (pid == 0)
	{
		printf("   ->[pid = %d]			child1: pid in if == 0 in child1\n", pid);
		new_fd = dup2(pipe_end, STDOUT_FILENO);
		printf("   ->child 1: zou in outfile moeten staan\n");
		execve("/bin/cat", av_exec, envp);
		printf("   ->dit zou niet geprint moeten worden\n");
	}
	waitpid(pid, NULL, 0);
	printf("   ->[pid = %d]		child1: na if == 0 van child1\n", pid);
}

void	child2(int fd_out, char **av_exec_2, char **envp)
{
	pid_t pid;
	pid_t first_pid;
	pid_t child_getpid;
	int new_fd;

	pid = fork();
	printf("   ->[pid = %d]		child2: pid als returen van fork in child1\n", pid);
	if (pid == 0)
	{
		printf("   ->[pid = %d]			child1: pid in if == 0 in child1\n", pid);
		new_fd = dup2(fd_out, STDOUT_FILENO);
		printf("   ->child 2: zou in outfile moeten staan\n");
		//fprintf(stderr, "new_fd = [%d]\n", new_fd); // deze komt nu dus ook in je outfile, of nu niet met fprintf
		//fprintf(stderr, "STDOUT_FILENO = [%d]\n", STDOUT_FILENO); // deze komt nu dus ook in je outfile, of nu niet met fprintf
		execve("/usr/bin/wc", av_exec_2, envp);
		printf("   ->dit zou niet geprint moeten worden\n");
	}
	waitpid(pid, NULL, 0);
	printf("   ->[pid = %d]		child2: na if == 0 van child1\n", pid);
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

	pipe(pipe_end);

	av_exec = malloc(sizeof(char *) * 4);
	av_exec[0] = "cat";
	av_exec[1] = "-e";
	av_exec[2] = av[1];
	av_exec[3] = NULL;

	av_exec_2 = malloc(sizeof(char *) * 3);
	av_exec_2[0] = "wc";
	//av_exec_2[1] = "-l";
	av_exec_2[1] = pipe_end[1];
	av_exec_2[2] = NULL;

	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[2], O_RDWR);
	first_pid = getpid();
	printf("   ->[pid = %d]		main: getpid\n", first_pid);
	child1(pipe_end[1], av_exec, envp);
	child2(fd_out, av_exec_2, envp);
	free(av_exec);
	first_pid = getpid();
	printf("   ->[pid = %d]		main: einde main\n", first_pid);
}