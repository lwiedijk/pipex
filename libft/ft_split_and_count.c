/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_and_count.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 18:25:09 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/10/13 13:00:38 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**ft_allocation_error(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static int	ft_string_count(const char *s, char dil_c)
{
	int	count;
	int	i;

	if (!s[0])
		return (0);
	i = 0;
	count = 0;
	while (s[i] && s[i] == dil_c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == dil_c)
		{
			count++;
			while (s[i] && s[i] == dil_c)
			{
				i++;
			}
			continue ;
		}
		i++;
	}
	if (s[i - 1] != dil_c)
		count = count + 1;
	return (count);
}

static void	ft_the_strings(char **substr, unsigned int *substrlen, char c)
{
	unsigned int	i;

	*substr = *substr + *substrlen;
	*substrlen = 0;
	i = 0;
	while (**substr && **substr == c)
		(*substr)++;
	while ((*substr)[i])
	{
		if ((*substr)[i] == c)
			break ;
		(*substrlen)++;
		i++;
	}
}

char	**ft_split_and_count(char const *s, char c, int *string_count)
{
	char			**ptr;
	char			*substr;
	unsigned int	substrlen;
	int				i;

	if (!s)
		return (NULL);
	*string_count = ft_string_count(s, c);
	ptr = (char **)malloc((ft_string_count(s, c) + 1) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	substr = (char *)s;
	substrlen = 0;
	while (i < ft_string_count(s, c))
	{
		ft_the_strings(&substr, &substrlen, c);
		ptr[i] = (char *)malloc((substrlen + 1) * sizeof(char));
		if (!ptr[i])
			return (ft_allocation_error(ptr));
		ft_strlcpy(ptr[i], substr, substrlen + 1);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
