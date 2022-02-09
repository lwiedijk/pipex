/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/28 13:43:03 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/01/28 13:46:22 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_3d_array(char ***cmd_array)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_array[i])
	{
		j = 0;
		while (cmd_array[i][j])
		{
			free(cmd_array[i][j]);
			j++;
		}
		free(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}
