/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 18:08:15 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/26 13:35:33 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = (void *)malloc(count * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	else
	{
		i = 0;
		while (i < count * size)
		{
			ptr[i] = '\0';
			i++;
		}
	}
	return ((void *)ptr);
}
