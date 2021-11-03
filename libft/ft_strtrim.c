/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 18:24:46 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/26 15:17:29 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ch_to_trim(const char *trim_str, char str_c)
{
	int	i;

	i = 0;
	while (trim_str[i] != '\0')
	{
		if (trim_str[i] == str_c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int	start(const char *str1, const char *trim1)
{
	int	i;

	i = 0;
	while (str1[i] && ch_to_trim(trim1, str1[i]))
	{
		i++;
	}
	return (i);
}

static int	end(const char *str2, const char *trim2, int left)
{
	int	j;
	int	substr_len;
	int	end_count;

	j = ft_strlen(str2);
	end_count = 0;
	while (j > left && ch_to_trim(trim2, str2[j - 1]))
	{
		j--;
		end_count++;
	}
	substr_len = ft_strlen(str2) - end_count;
	return (substr_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	int		left;
	int		right;

	if (!s1 || !set)
		return (NULL);
	if (s1 && set)
	{
		left = start(s1, set);
		right = end(s1, set, left);
		trimmed_str = ft_substr(s1, left, (right - left));
		return (trimmed_str);
	}
	return (0);
}
