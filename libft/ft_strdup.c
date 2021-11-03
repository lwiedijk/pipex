/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 18:13:05 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/26 15:13:03 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	ptr = (char *)malloc((i + 1) * sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	else
	{
		i = 0;
		while (s1[i])
		{
			ptr[i] = s1[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
