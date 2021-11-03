/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 14:45:48 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/26 16:56:11 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "libft.h"

static void	*copy_backward(unsigned char *dstp,
				const unsigned char *srcp, size_t len)
{
	while (len > 0)
	{
		len--;
		dstp[len] = srcp[len];
	}
	return (dstp);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dstp;
	const unsigned char	*srcp;
	size_t				i;

	dstp = (unsigned char *)dst;
	srcp = (unsigned char *)src;
	if (!dstp && !srcp)
		return (NULL);
	if (srcp < dstp)
		return (copy_backward(dstp, srcp, len));
	else
	{
		i = 0;
		while (i < len)
		{
			dstp[i] = srcp[i];
			i++;
		}
	}
	return (dst);
}
