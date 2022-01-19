/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:18:32 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/19 09:24:59 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	t_exec_vectors	exec_vectors;
	t_all_fd		all_fd;
	t_pipe_ends		*array_of_ends;
	char			***cmd_vectors;
	int				cmd_count;

	cmd_count = ac - 3;
	
	array_of_ends = (t_pipe_ends *)malloc(sizeof(t_pipe_ends) * (cmd_count - 1));
	//array_of_ends[0].pipe_ends[1] = 9;
	//fprintf(stderr, "pipe_ends = %d\n", array_of_ends[0].pipe_ends[1]);

	initialize(&exec_vectors, &all_fd);
	if (ac < 5)
		error_and_exit(USAGE, &exec_vectors);
	cmd_vectors = argument_parser(&exec_vectors, av, (ac - 2));
	//if (pipe(all_fd.pipe_end) == -1)
	//	error_and_exit(SYS_CALL_ERR, &exec_vectors);
	//if (pipe(all_fd.pipe_end_two) == -1)
	//	error_and_exit(SYS_CALL_ERR, &exec_vectors);
	all_fd.fd_in = open(av[1], O_RDONLY);
	all_fd.fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, MODE_RW_R_R);
	if (all_fd.fd_in < 0 || all_fd.fd_out < 0) //dit moet dus precieser voor return error ding
		error_open(av[1], &exec_vectors);
	fork_processes(&exec_vectors, &all_fd, envp, cmd_count, cmd_vectors);
	free_2d_array(exec_vectors.vector1);
	free_2d_array(exec_vectors.vector2);
	exit(EXIT_SUCCESS);
}
