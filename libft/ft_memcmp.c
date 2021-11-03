/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 14:48:59 by lwiedijk      #+#    #+#                 */
/*   Updated: 2020/11/28 10:02:02 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1p;
	const unsigned char	*s2p;
	size_t				i;

	i = 0;
	s1p = (const unsigned char *)s1;
	s2p = (const unsigned char *)s2;
	if (s1p == s2p || n == 0)
	{
		return (0);
	}
	while (i < n)
	{
		if (s1p[i] != s2p[i])
		{
			return (s1p[i] - s2p[i]);
		}
		i++;
	}
	return (0);
}
