/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 10:12:22 by lwiedijk      #+#    #+#                 */
/*   Updated: 2020/11/28 10:02:36 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*str;
	unsigned char		*mem;
	size_t				i;

	i = 0;
	str = (const unsigned char *)src;
	mem = (unsigned char *)dst;
	if (!str && !mem)
		return (NULL);
	while (i < n)
	{
		mem[i] = str[i];
		i++;
	}
	return ((unsigned char *)dst);
}
