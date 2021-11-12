/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:18:32 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/11/12 11:47:40 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_exec_vectors	exec_vectors;
	t_all_fd		all_fd;

	initialize(&exec_vectors, &all_fd);
	if (ac != 5)
		error_and_exit(USAGE, &exec_vectors);
	argument_parser(&exec_vectors, av);
	if (pipe(all_fd.pipe_end) == -1)
		error_and_exit(SYS_CALL_ERR, &exec_vectors);
	all_fd.fd_in = open(av[1], O_RDONLY);
	all_fd.fd_out = open(av[4], O_CREAT | O_RDWR | O_TRUNC, MODE_RW_R_R);
	if (all_fd.fd_in < 0 || all_fd.fd_out < 0)
		error_and_exit(SYS_CALL_ERR, &exec_vectors);
	fork_processes(&exec_vectors, &all_fd, envp);
	free_2d_array(exec_vectors.vector1);
	free_2d_array(exec_vectors.vector2);
}
