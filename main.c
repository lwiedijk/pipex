/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:18:32 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/26 17:30:41 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	t_all_fd		all_fd;
	char			***cmd_vectors;
	char			buffer[1];
	int				cmd_count;

	buffer[0] = '\0';
	cmd_count = ac - 3;
	cmd_vectors = NULL;
	initialize(&all_fd);
	if (ac < 5)
		error_and_exit(USAGE, cmd_vectors);
	cmd_vectors = argument_parser(av, (ac - 3));
	all_fd.fd_in = open(av[1], O_RDONLY);
	all_fd.fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, MODE_RW_R_R);
	if (all_fd.fd_in < 0 || all_fd.fd_out < 0)
	{ //dit moet dus precieser voor return error ding
		error_message_and_continue(av[1]);
		all_fd.fd_in = -1;
		//all_fd.fd_in = open(buffer, O_RDONLY);
	}
	fork_processes(&all_fd, envp, cmd_count, cmd_vectors);
	free_3d_array(cmd_vectors); //renmame?!
	//system ("leaks pipex");
	exit(EXIT_SUCCESS);
}
