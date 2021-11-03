/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 12:33:37 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/26 13:30:20 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	overflow(int plu_min, long long int result, const char *str, int i)
{
	if (plu_min == -1 && str[i] > '8')
		return (0);
	if (plu_min == -1 && result > 922337203685477580)
		return (0);
	if (plu_min == 1 && str[i] > '7')
		return (-1);
	if (plu_min == 1 && result > 922337203685477580)
		return (-1);
	else
	{
		result = (result * 10) + (str[i] - '0');
		return (result * plu_min);
	}
}

int	ft_atoi(const char *str)
{
	int					i;
	int					plu_min;
	long long int		result;

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
		if (result >= 922337203685477580)
			return (overflow(plu_min, result, str, i));
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * plu_min);
}
