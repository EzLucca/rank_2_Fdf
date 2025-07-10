/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:55:13 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 17:17:36 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

bool	color_check(const char *color)
{
	int i;

	if (!color)
		return (false);
	if (color[0] != '0' || color[1] != 'x')
		return (false);
	i = 2;
	if (color[i] == '\0')
		return (false);
	while (color[i])
	{
		if (!((color[i] >= '0' && color[i] <= '9') ||
					(color[i] >= 'a' && color[i] <= 'f') ||
					(color[i] >= 'A' && color[i] <= 'F')))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	number_check(const char *str)
{
	int i = 0;

	if (!str || str[0] == '\0')
		return (false);
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	valid_point(char *token)
{
	char **point;

	if (ft_strchr(token, ','))
	{
		point = fdf_split(token, ',');
		if(!point || !number_check(point[0]) || !color_check(point[1]))
			return (ft_free_array(point), false);
	}
	else if (!number_check(token))
		return (false);
	return(true);
}

bool	points_check(char *line)
{
	char	**split;
	int		i;

	i = 0;
	split = fdf_split(line, ' ');
	if (!split)
		return (free(line), false);
	while (split[i])
	{
		if (split[i][0] != '\0' && !valid_point(split[i]))
			return (ft_free_array(split), free(line), false);
		i++;
	}
	ft_free_array(split);
	return (true);
}
