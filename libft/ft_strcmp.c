/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 09:24:35 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/26 15:12:15 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	idex;

	idex = 0;
	while (s1[idex] != '\0' || s2[idex] != '\0')
	{
		if (s1[idex] == s2[idex])
		{
			idex++;
		}
		else
			return (s1[idex] - s2[idex]);
	}
	return (0);
}
