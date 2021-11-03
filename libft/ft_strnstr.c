/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 14:55:51 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/26 15:16:38 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (needle[0] == '\0')
	{
		return ((char *)haystack);
	}
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		if (haystack[i] == needle[0])
		{
			while (needle[j] == haystack[i + j] && (i + j) < len)
			{
				j++;
				if (!needle[j])
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (NULL);
}
