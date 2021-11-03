/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 14:53:26 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/26 15:11:50 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (s[i] == '\0' && c == '\0')
		return ((char *)s);
	while (s[i])
	{
		if (s[i] == c)
		{
			return ((char *)s + i);
		}
		if (c == '\0')
			return ((char *)s + ft_strlen(s));
		i++;
	}
	return (NULL);
}
