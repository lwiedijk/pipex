/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 11:04:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/19 09:48:28 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h> //wait

//static void	child1(char **envp, t_all_fd *all_fd, t_exec_vectors *exec_vectors)
//{
//	char	*path;
//
//	//exit(120);
//	close_and_check(all_fd->fd_out, exec_vectors);
//	path = path_parser(exec_vectors->vector1[0], envp, exec_vectors);
//	if (dup2(all_fd->fd_in, STDIN_FILENO) == -1)
//		error_and_exit(SYS_CALL_ERR, exec_vectors);
//	if (dup2(all_fd->pipe_end[1], STDOUT_FILENO) == -1)
//		error_and_exit(SYS_CALL_ERR, exec_vectors);
//	close_and_check(all_fd->pipe_end[0], exec_vectors);
//	close_and_check(all_fd->pipe_end[1], exec_vectors);
//	close_and_check(all_fd->fd_in, exec_vectors);
//	execve(path, exec_vectors->vector1, envp);
//	fprintf(stderr, "exec1 has failed\n");
//	error_and_exit(SYS_CALL_ERR, exec_vectors);
//}
//
//static void	child2(char **envp, t_all_fd *all_fd, t_exec_vectors *exec_vectors)
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
//	fprintf(stderr, "exec2 has failed\n");
//	error_and_exit(SYS_CALL_ERR, exec_vectors);
//}

//static void	launch_child_process(char **envp, t_all_fd *all_fd, t_exec_vectors *exec_vectors,
//									char ***cmd_vectors, int child_count, int cmd_count, int tmp_previous)
//{
//	//static int!?
//	char	*path;
//	int	fd_bool;
//	fd_bool = child_count % 2;
//	fprintf(stderr, "fd_bool = %d\n", fd_bool);
//	(void)*all_fd;
//	(void)tmp_previous;
//	(void)envp;
//
//	//if (tmp_previous)
//	//		dup tmp previous naar stdin (beter in child) (previous_pipe moet mee met child, dub dit naar stdin)
//
//
//	if (!fd_bool)
//	{
//		if (child_count == 0)
//		{
//			if (dup2(all_fd->fd_in, STDIN_FILENO) == -1)
//			error_and_exit(SYS_CALL_ERR, exec_vectors);
//		}
//		if (dup2(all_fd->pipe_end[0], STDIN_FILENO) == -1)
//			error_and_exit(SYS_CALL_ERR, exec_vectors);
//		if (child_count == cmd_count)
//		{
//			if (dup2(all_fd->fd_out, STDOUT_FILENO) == -1)
//				error_and_exit(SYS_CALL_ERR, exec_vectors);
//		}
//		else
//		{
//			if (dup2(all_fd->pipe_end_two[1], STDOUT_FILENO) == -1)
//				error_and_exit(SYS_CALL_ERR, exec_vectors);
//		}
//	}
//	else
//	{
//		if (dup2(all_fd->pipe_end_two[0], STDIN_FILENO) == -1)
//			error_and_exit(SYS_CALL_ERR, exec_vectors);
//		if (child_count == cmd_count)
//		{
//			if (dup2(all_fd->fd_out, STDOUT_FILENO) == -1)
//				error_and_exit(SYS_CALL_ERR, exec_vectors);
//		}
//		else
//		{
//			if (dup2(all_fd->pipe_end[1], STDOUT_FILENO) == -1)
//				error_and_exit(SYS_CALL_ERR, exec_vectors);
//		}
//		
//	}
//
//	close_and_check(all_fd->fd_in, exec_vectors);
//	close_and_check(all_fd->pipe_end[1], exec_vectors);
//	close_and_check(all_fd->pipe_end[0], exec_vectors);
//	close_and_check(all_fd->pipe_end_two[1], exec_vectors);
//	close_and_check(all_fd->pipe_end_two[0], exec_vectors);
//	close_and_check(all_fd->fd_out, exec_vectors);
//	
//	path = path_parser(cmd_vectors[child_count][0], envp, exec_vectors);
//	//fprintf(stderr, "cmd_vectors = %s at child_count [%d] \n", cmd_vectors[child_count][0], child_count);
//	execve(path, cmd_vectors[child_count], envp);
//	error_and_exit(SYS_CALL_ERR, exec_vectors);
//}

static void	launch_child_process(char **envp, t_exec_vectors *exec_vectors, char ***cmd_vectors, t_all_fd *all_fd,
					int child_count, int cmd_count, int previous_pipe_to_read_from)
{
	char *path;
	path = NULL;

	//fprintf(stderr, "child_count is [%d]\n", child_count);
	//fprintf(stderr, "cmd_vector[%d] is [%s]\n", child_count, cmd_vectors[child_count][0]);
	//fprintf(stderr, "prev_pipe is [%d]\n", previous_pipe_to_read_from);
	//fprintf(stderr, "pipe_end_[1] is [%d]\n", all_fd->pipe_end[1]);
	
	if (previous_pipe_to_read_from == 0)
		dup2(all_fd->fd_in, STDIN_FILENO);
	else
		dup2(previous_pipe_to_read_from, STDIN_FILENO);
	if ((child_count + 1) == cmd_count)
		dup2(all_fd->fd_out, STDOUT_FILENO);
	else
		dup2(all_fd->pipe_end[1], STDOUT_FILENO);
	
	
	int check = close(all_fd->pipe_end[1]);
	fprintf(stderr, "close check = [%d]\n", check);
	//close(all_fd->pipe_end[0]);
	//close_and_check(all_fd->fd_in, exec_vectors);
	//close_and_check(all_fd->pipe_end[1], exec_vectors);
	//close_and_check(all_fd->pipe_end[0], exec_vectors);
	//close_and_check(all_fd->fd_out, exec_vectors);

	path = path_parser(cmd_vectors[child_count][0], envp, exec_vectors);
	//fprintf(stderr, "cmd_vectors = %s at child_count [%d] \n", cmd_vectors[child_count][0], child_count);
	execve(path, cmd_vectors[child_count], envp);
	error_and_exit(SYS_CALL_ERR, exec_vectors);
}

void	initialize(t_exec_vectors *exec_vectors, t_all_fd *all_fd)
{
	exec_vectors->vector1 = NULL;
	exec_vectors->vector2 = NULL;
	all_fd->fd_in = 0;
	all_fd->fd_out = 0;
	all_fd->pipe_end[0] = 0;
	all_fd->pipe_end[1] = 0;
	all_fd->pipe_end_two[0] = 0;
	all_fd->pipe_end_two[1] = 0;
}

void	fork_processes(t_exec_vectors *exec_vectors,
			t_all_fd *all_fd, char **envp, int cmd_count, char ***cmd_vectors)
{
	int		status;
	int		exitstatus;
	int		child_count;
	int		previous_pipe_to_read_from;
	int		current_pipe_to_write_to;
	//int		pipe_end[2];
	pid_t	wp;
	pid_t	lastpid;
	(void)*all_fd;
	(void)cmd_vectors;
	(void)envp;

	child_count = 0;
	all_fd->pipe_end[0] = 0;
	//cmd_count = 8;
	while (child_count < cmd_count)
	{
		fprintf(stderr, "cmd_vector[%d] is [%s]\n", child_count, cmd_vectors[child_count][0]);
		previous_pipe_to_read_from = all_fd->pipe_end[0]; //(je moet leesdeel van de vorige gebruiken terwijl je de nieuwe gebruikt)
		if ((child_count + 1) != cmd_count)
		{
			pipe(all_fd->pipe_end);
			current_pipe_to_write_to = all_fd->pipe_end[1];
		}
		lastpid = fork();
		if (lastpid == -1)
			error_and_exit(SYS_CALL_ERR, exec_vectors);
		else if (lastpid == 0)
			//exit(33);
			launch_child_process(envp, exec_vectors, cmd_vectors, all_fd, child_count, cmd_count, previous_pipe_to_read_from);
		close(current_pipe_to_write_to);
		if (previous_pipe_to_read_from != 0)
			close(previous_pipe_to_read_from);
		//fprintf(stderr, "previous_pipe_to_read_from = [%d]\n", previous_pipe_to_read_from);
		//fprintf(stderr, "current_pipe_to_write_to = [%d]\n", current_pipe_to_write_to);
		//system("lsof -c pipex");
		child_count++;
	}
	//fprintf(stderr, "childcount = [%d]\n", child_count);
	//system("lsof -c pipex");
	while (1)
	{
		wp = waitpid(-1, &status, 0);
		fprintf(stderr, "child [%d] closed\n", wp);
		if (wp == lastpid)
			exitstatus = WEXITSTATUS(status);
		else if (wp == -1)
			break ;
	}


	//pid_1 = fork();
	//if (pid_1 == -1)
	//	error_and_exit(SYS_CALL_ERR, exec_vectors);
	//if (pid_1 == 0)
	//	child1(envp, all_fd, exec_vectors);
	//pid_2 = fork();
	//if (pid_2 == -1)
	//	error_and_exit(SYS_CALL_ERR, exec_vectors);
	//if (pid_2 == 0)
	//	child2(envp, all_fd, exec_vectors);
	//close_and_check(all_fd->pipe_end[0], exec_vectors);
	//close_and_check(all_fd->pipe_end[1], exec_vectors);
	//close_and_check(all_fd->fd_in, exec_vectors);
	//close_and_check(all_fd->fd_out, exec_vectors);
	//wait_return1 = waitpid(pid_1, &status, 0);
	////printf("status = [%d]\n", status);
	//printf("exitstatus = [%d]\n", WEXITSTATUS(status));
	//printf("wait_return1 = [%d]\n", wait_return1);
	//printf("child1_pid = [%d]\n", pid_1);
	//wait_return2 = waitpid(pid_2, &status, 0);
	//// waid pid returnd -1 als er niks meer is
	////printf("status = [%d]\n", status);
	//printf("exitstatus = [%d]\n", WEXITSTATUS(status));
	//printf("wait_return2 = [%d]\n", wait_return2);
	//printf("child2_pid = [%d]\n", pid_2);
}


//wp = waitpid(paramterers)
//while (wp != -1)
//{
//	if (wp == lastpid)
//		exitstatus = wp
//	wp = waitpid(paramteres)
//}

	//wp = waitpid(-1, &status, 0);
	//while (wp != -1)
	//{
	//	if (wp == lastpid)
	//		exitstatus = WEXITSTATUS(status);
	//	wp = waitpid(-1, &status, 0);
	//}