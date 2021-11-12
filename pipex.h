/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 11:07:46 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/11/12 11:47:00 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define MODE_RW_R_R 0644
# define TRUE 1
# define FALSE 0

typedef enum e_error_status
{
	OK,
	ERROR,
	SYS_CALL_ERR,
	USAGE,
	MALLOC_FAIL,
}	t_error_status;

typedef struct s_exec_vectors
{
	char	**vector1;
	char	**vector2;
}					t_exec_vectors;

typedef struct s_all_fd
{
	int	fd_in;
	int	fd_out;
	int	pipe_end[2];
}					t_all_fd;

/* pipec.c */
void	fork_processes(t_exec_vectors *exec_vectors,
			t_all_fd *all_fd, char **envp);
void	initialize(t_exec_vectors *exec_vectors, t_all_fd *all_fd);

/* parser.c */
void	argument_parser(t_exec_vectors *exec_vectors, char **av);
char	*path_parser(char *cmd, char **envp, t_exec_vectors *exec_vectors);

/* free_and_exit.c */
void	close_and_check(int fd, t_exec_vectors *exec_vectors);
void	error_and_exit(int status, t_exec_vectors *exec_vectors);
void	free_on_error(t_exec_vectors *exec_vectors);
void	free_2d_array(char **cmd_array);

#endif
