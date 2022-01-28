/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:07:46 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/28 14:10:12 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define MODE_RW_R_R 0644
# define MODE_R_R_R 0444
# define TRUE 1
# define FALSE 0
# define INFILE_OUTFILE_EXECPATH 3
# define INFILE_EXECPATH 2
# define OUTFILE 1
# define INFILE 1

#include <stdbool.h>

//typedef enum e_error_status
//{
//	OK,
//	ERROR,
//	SYS_CALL_ERR,
//	USAGE,
//	MALLOC_FAIL,
//	NO_EXISTING_PATH,
//}	t_error_status;

typedef struct s_all_fd
{
	int	fd_in;
	int	fd_out;
	int	pipe_end[2];
	int	exitstatus;
}					t_all_fd;

/* pipex.c */
void	fork_processes(t_all_fd *all_fd, char **envp, int cmd_count, char ***cmd_vectors);

/* parser.c */
char	***argument_parser(char **av, int ac);
char	*path_parser(char *cmd, char **envp);

/* utils.c */
void	close_and_check(int fd);
bool	is_path(char *cmd);
void	initialize(t_all_fd *all_fd);

/* error.c */
void	error_message_and_continue(char *error_object);
void	error_message_and_exit(void);
void	pipex_error_and_exit(void);
void	command_not_found(char *error_object);
void	close_and_check(int fd);

/* free.c */
void	free_2d_array(char **cmd_array);
void	free_3d_array(char ***cmd_array);

#endif
