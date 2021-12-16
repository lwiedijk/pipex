/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 11:04:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/12/16 13:40:15 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h> //wait

static void	child1(char **envp, t_all_fd *all_fd, t_exec_vectors *exec_vectors)
{
	char	*path;

	//exit(120);
	close_and_check(all_fd->fd_out, exec_vectors);
	path = path_parser(exec_vectors->vector1[0], envp, exec_vectors);
	if (dup2(all_fd->fd_in, STDIN_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
	if (dup2(all_fd->pipe_end[1], STDOUT_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
	close_and_check(all_fd->pipe_end[0], exec_vectors);
	close_and_check(all_fd->pipe_end[1], exec_vectors);
	close_and_check(all_fd->fd_in, exec_vectors);
	execve(path, exec_vectors->vector1, envp);
	fprintf(stderr, "exec1 has failed\n");
	error_and_exit(SYS_CALL_ERR, exec_vectors);
}

static void	child2(char **envp, t_all_fd *all_fd, t_exec_vectors *exec_vectors)
{
	char	*path;

	//exit(122);
	close_and_check(all_fd->fd_in, exec_vectors);
	path = path_parser(exec_vectors->vector2[0], envp, exec_vectors);
	if (dup2(all_fd->pipe_end[0], STDIN_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
	if (dup2(all_fd->fd_out, STDOUT_FILENO) == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
	close_and_check(all_fd->pipe_end[1], exec_vectors);
	close_and_check(all_fd->pipe_end[0], exec_vectors);
	close_and_check(all_fd->fd_out, exec_vectors);
	execve(path, exec_vectors->vector2, envp);
	fprintf(stderr, "exec2 has failed\n");
	error_and_exit(SYS_CALL_ERR, exec_vectors);
}

//static void	child_process(char **envp, t_all_fd *all_fd, t_exec_vectors *exec_vectors)
//{
//	char	*path;
//
//	//exit(122);
//	close_and_check(all_fd->fd_in, exec_vectors);
//	path = path_parser(exec_vectors->vector2[0], envp, exec_vectors);
//	if (dup2(all_fd->pipe_end[0], STDIN_FILENO) == -1)
//		error_and_exit(SYS_CALL_ERR, exec_vectors);
//	if (dup2(all_fd->fd_out, STDOUT_FILENO) == -1)
//		error_and_exit(SYS_CALL_ERR, exec_vectors);
//	close_and_check(all_fd->pipe_end[1], exec_vectors);
//	close_and_check(all_fd->pipe_end[0], exec_vectors);
//	close_and_check(all_fd->fd_out, exec_vectors);
//	execve(path, exec_vectors->vector2, envp);
//	error_and_exit(SYS_CALL_ERR, exec_vectors);
//}

void	initialize(t_exec_vectors *exec_vectors, t_all_fd *all_fd)
{
	exec_vectors->vector1 = NULL;
	exec_vectors->vector2 = NULL;
	all_fd->fd_in = 0;
	all_fd->fd_out = 0;
	all_fd->pipe_end[0] = 0;
	all_fd->pipe_end[1] = 0;
}

void	fork_processes(t_exec_vectors *exec_vectors,
			t_all_fd *all_fd, char **envp, int cmd_count)
{
	pid_t	pid_1;
	pid_t	pid_2;
	pid_t	wait_return1;
	pid_t	wait_return2;
	int		status;

	int		child_count;
	pid_t	lastpid;

	child_count = 0;
	while (child_count < cmd_count)
	{
		lastpid = fork();
		if (lastpid == -1)
			error_and_exit(SYS_CALL_ERR, exec_vectors);
		else if (lastpid == 0)
			child1(envp, all_fd, exec_vectors);
		child_count++;
	}
	pid_1 = fork();
	if (pid_1 == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
	if (pid_1 == 0)
		child1(envp, all_fd, exec_vectors);
	pid_2 = fork();
	if (pid_2 == -1)
		error_and_exit(SYS_CALL_ERR, exec_vectors);
	if (pid_2 == 0)
		child2(envp, all_fd, exec_vectors);
	close_and_check(all_fd->pipe_end[0], exec_vectors);
	close_and_check(all_fd->pipe_end[1], exec_vectors);
	close_and_check(all_fd->fd_in, exec_vectors);
	close_and_check(all_fd->fd_out, exec_vectors);
	wait_return1 = waitpid(pid_1, &status, 0);
	//printf("status = [%d]\n", status);
	printf("exitstatus = [%d]\n", WEXITSTATUS(status));
	printf("wait_return1 = [%d]\n", wait_return1);
	printf("child1_pid = [%d]\n", pid_1);
	wait_return2 = waitpid(pid_2, &status, 0);
	// waid pid returnd -1 als er niks meer is
	//printf("status = [%d]\n", status);
	printf("exitstatus = [%d]\n", WEXITSTATUS(status));
	printf("wait_return2 = [%d]\n", wait_return2);
	printf("child2_pid = [%d]\n", pid_2);
}


//wp = waitpid(paramterers)
//while (wp != -1)
//{
//	if (wp == lastpid)
//		exitstatus = wp
//	wp = waitpid(paramteres)
//}