/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 11:12:03 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/03/09 17:28:51 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_numlen_base(long value, int base)
{
	int	len;

	len = 0;
	if (value < 0)
	{
		value = value * -1;
		len++;
	}
	if (value == 0)
		len++;
	while (value)
	{
		value = value / base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(long long value, int base, char *hex_case)
{
	int		l;
	int		remainder;
	char	*output;

	l = ft_numlen_base(value, base);
	output = (char *)malloc(sizeof(char) * l + 1);
	if (output == NULL)
		return (NULL);
	if (value == 0)
		output[0] = '0';
	if (value < 0 && base == 10)
	{
		output[0] = '-';
		value = value * -1;
	}
	output[l] = '\0';
	while (value)
	{
		l--;
		remainder = value % base;
		value = value / base;
		output[l] = hex_case[remainder];
	}
	return (output);
}
