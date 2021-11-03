/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 18:25:33 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/26 13:37:47 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	malloc_size(long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	if (nb == 0)
		len++;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		l;

	num = n;
	l = malloc_size(num);
	str = (char *)malloc(sizeof(char) * (l + 1));
	if (str == NULL)
		return (NULL);
	str[l] = '\0';
	l--;
	if (num == 0)
		str[0] = '0';
	if (num < 0)
	{
		str[0] = '-';
		num = num * -1;
	}
	while (num > 0)
	{
		str[l] = num % 10 + '0';
		num = num / 10;
		l--;
	}
	return (str);
}
