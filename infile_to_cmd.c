/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   infile_to_cmd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 11:27:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/10/28 16:17:50 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	int i;
	int	fd_in;
	int fd_out;
	char **av_exec;
	pid_t child;
	int new_fd;

	av_exec = malloc(sizeof(char *) * 4);
	av_exec[0] = "cat";
	av_exec[1] = "-e";
	//av_exec[1] = NULL;
	av_exec[2] = av[1];
	av_exec[3] = NULL;

	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[2], O_RDWR);
	printf("fd_out = [%d]\n", fd_out);
	child = fork();
	if (child == 0)
	{
		printf("blabla\n");
		new_fd = dup2(fd_out, STDOUT_FILENO);
		printf("new_fd = [%d]\n", new_fd); // deze komt nu dus ook in je outfile
		printf("STDOUT_FILENO = [%d]\n", STDOUT_FILENO); // deze komt nu dus ook in je outfile
		execve("/bin/cat", av_exec, envp);
	}
	waitpid(child, NULL, 0);
	free(av_exec);
	printf("   ljslfjsl\n");
}