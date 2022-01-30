/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:18:32 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/30 15:00:19 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_metadata	data;
	t_all_fd	all_fd;
	char		***cmd_vectors;

	data.cmd_count = ac - INFILE_OUTFILE_EXECPATH;
	cmd_vectors = NULL;
	initialize_data_struct(&data);
	initialize_fd_struct(&all_fd);
	if (ac < 5)
		pipex_error_and_exit();
	cmd_vectors = argument_parser(av, data.cmd_count);
	all_fd.fd_in = open(av[INFILE], O_RDONLY);
	if (all_fd.fd_in < 0)
		error_message_and_continue(av[INFILE]);
	all_fd.fd_out = open(av[ac - OUTFILE],
			O_CREAT | O_RDWR | O_TRUNC, MODE_RW_R_R); //write only?
	if (all_fd.fd_out < 0)
		error_message_and_continue(av[ac - OUTFILE]);
	pipex(&data, &all_fd, envp, cmd_vectors);
	free_3d_array(cmd_vectors);
	exit(data.exitstatus);
}
