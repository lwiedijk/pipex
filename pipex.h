/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:07:46 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/30 14:37:59 by lwiedijk      ########   odam.nl         */
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

# include <stdbool.h>

typedef struct s_all_fd
{
	int	fd_in;
	int	fd_out;
	int	pipe_end[2];
	int	previous_read_end;
}					t_all_fd;

typedef struct s_metadata
{
	int		child_count;
	int		cmd_count;
	pid_t	lastpid;
	int		exitstatus;
}					t_metadata;

/* pipex.c */
void	pipex(t_metadata *metadata, t_all_fd *all_fd,
			char **envp, char ***cmd_vectors);

/* child_process.c */
void	execute_cmd(t_metadata *medadata, t_all_fd *all_fd,
			char **envp, char ***cmd_vectors);

/* parser.c */
char	***argument_parser(char **av, int ac);
char	*path_parser(char *cmd, char **envp);

/* utils.c */
void	close_and_check(int fd);
bool	is_path(char *cmd);
void	initialize_fd_struct(t_all_fd *all_fd);
void	initialize_data_struct(t_metadata *data);

/* error.c */
void	error_message_and_exit(void);
void	error_message_and_continue(char *error_object);
void	pipex_error_and_exit(void);
void	command_not_found(char *error_object);

/* free.c */
void	free_2d_array(char **cmd_array);
void	free_3d_array(char ***cmd_array);

#endif
