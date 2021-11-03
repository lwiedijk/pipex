/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 14:51:12 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/26 15:12:36 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, char *src)
{
	int	idex;

	idex = 0;
	while (src[idex] != '\0')
	{
		dest[idex] = src[idex];
		idex++;
	}
	dest[idex] = '\0';
	return (dest);
}
