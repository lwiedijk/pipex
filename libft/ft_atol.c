/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 12:33:37 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/10/13 13:12:28 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

long int	ft_atol(const char *str)
{
	int				i;
	int				plu_min;
	long int		result;

	i = 0;
	plu_min = 1;
	result = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			plu_min *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * plu_min);
}
