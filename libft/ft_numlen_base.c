/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlen_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 15:33:10 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/03/09 18:02:44 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_numlen_base(long value, int base)
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
