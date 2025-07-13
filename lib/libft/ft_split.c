/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:27:20 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/08 14:35:37 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This should return the len of the substring
static int	substr_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

//This function count the word of the string
int	count_tokens(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			s += substr_len(s, c);
		}
		else
			s++;
	}
	return (count);
}

//Free every array if one of them are not properly allocated
static void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}

//Split the string in substring
char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (count_tokens(s, c) + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			array[i] = ft_substr(s, 0, substr_len(s, c));
			if (!array[i++])
				return (free_array(array));
			s += substr_len(s, c);
		}
		else
			s++;
	}
	array[i] = NULL;
	return (array);
}
