/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:07:46 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/02/10 13:16:03 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define MODE_RW_R_R 0644
# define INFILE_OUTFILE_EXECPATH 3
# define INFILE_EXECPATH 2
# define OUTFILE 1
# define INFILE 1

# include <stdbool.h>

typedef enum e_error_code
{
	OK,
	BONUS,
	HEREDOC,
}	t_error_code;

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
	char	*limiter;
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
char	***argument_parser(char **av, int cmd_c, t_metadata *data);
char	*path_parser(char *cmd, char **envp);

/* utils.c */
void	close_and_check(int fd);
bool	is_path(char *cmd);
void	initialize_fd_struct(t_all_fd *all_fd);
void	initialize_data_struct(t_metadata *data);

/* error.c */
void	error_message_and_exit(void);
void	error_message_and_continue(char *error_object);
void	pipex_usage_error(void);
void	pipex_bonus_usage_error(int error_code);
void	command_not_found(char *error_object);

/* free.c */
void	free_2d_array(char **cmd_array);
void	free_3d_array(char ***cmd_array);

/* here_doc.c */
void	here_doc_handling(t_all_fd *all_fd, t_metadata *data);

#endif
