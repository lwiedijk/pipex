/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base_unsigned.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 13:27:14 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/03/19 16:42:23 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_numlen_unsigned(unsigned long long value, int base)
{
	int	len;

	len = 0;
	if (value == 0)
		len++;
	while (value)
	{
		value = value / base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base_unsigned(unsigned long long value, int base,
char *hex_case)
{
	int		l;
	int		remainder;
	char	*output;

	l = ft_numlen_unsigned(value, base);
	output = (char *)malloc(sizeof(char) * l + 1);
	if (output == NULL)
		return (NULL);
	if (value == 0)
		output[0] = '0';
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
