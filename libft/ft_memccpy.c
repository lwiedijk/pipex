/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 14:42:07 by lwiedijk      #+#    #+#                 */
/*   Updated: 2020/11/28 10:01:02 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dstp;
	const unsigned char	*srcp;
	unsigned char		uc;
	size_t				i;

	i = 0;
	uc = (unsigned char)c;
	dstp = (unsigned char *)dst;
	srcp = (const unsigned char *)src;
	while (i < n)
	{
		dstp[i] = srcp[i];
		if (dstp[i] == uc)
		{
			return (dst + i + 1);
		}
		i++;
	}
	return (NULL);
}
