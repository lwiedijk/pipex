/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 11:04:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/10/22 13:00:00 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> //perror

void	pipex(int f1, int f2)
{
	int		pipe_end[2];
	pid_t	parent_pid;

	pipe(pipe_end);
	parent_pid = fork();
	if (parent_pid < 0)
	{
		perror("Fork: ");
		return (EXIT_FAILURE);
	}
	if (!parent_pid) //when returnes 0 we are in child process
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);

}

int	main(int ac, char **av, char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		printf("envp = [%s]\n", envp[i]);
		i++;
	}
}