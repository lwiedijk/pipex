/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 09:16:04 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/10 13:30:04 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "pipex.h"
#include "libft.h"

static void	normal_file_handling(t_all_fd *all_fd, int ac, char **av)
{
	all_fd->fd_in = open(av[INFILE], O_RDONLY);
	if (all_fd->fd_in < 0)
		error_message_and_continue(av[INFILE]);
	all_fd->fd_out = open(av[ac - OUTFILE],
			O_CREAT | O_WRONLY | O_TRUNC, MODE_RW_R_R);
}

static void	call_heredoc(t_metadata *data, t_all_fd *all_fd, int ac, char **av)
{
	if (ac < 6)
		pipex_bonus_usage_error(HEREDOC);
	data->limiter = av[2];
	here_doc_handling(all_fd, data);
	all_fd->fd_out = open(av[ac - OUTFILE],
			O_CREAT | O_WRONLY | O_APPEND, MODE_RW_R_R);
}

int	main(int ac, char **av, char **envp)
{
	t_metadata	data;
	t_all_fd	all_fd;
	char		***cmd_vectors;

	if (ac < 5)
		pipex_bonus_usage_error(BONUS);
	data.cmd_count = ac - INFILE_OUTFILE_EXECPATH;
	cmd_vectors = NULL;
	initialize_data_struct(&data);
	initialize_fd_struct(&all_fd);
	if (!ft_strcmp(av[INFILE], "here_doc"))
		call_heredoc(&data, &all_fd, ac, av);
	else
		normal_file_handling(&all_fd, ac, av);
	cmd_vectors = argument_parser(av, data.cmd_count, &data);
	if (all_fd.fd_out < 0)
		error_message_and_continue(av[ac - OUTFILE]);
	pipex(&data, &all_fd, envp, cmd_vectors);
	free_3d_array(cmd_vectors);
	exit(data.exitstatus);
}
