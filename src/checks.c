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

// TODO: Function bigger than 25 lines
// problem with the file descriptor
// get_next_line should be in a while
bool	points_check(t_map *map)
{
	char	**split;
	char	*line;
	char	**point;
	int		i;
	int		j;

	ft_printf("%d\n", map->fd);
	i = 0;
	j = 0;
	point = NULL;
	split = NULL;
	line = get_next_line(map->fd);
	ft_printf("%s\n", line);
	if (!line)
		return (false);
	split = fdf_split(line, ' ');
	if (!split)
		return (false);
	while (split[i])
	{
		if (ft_strchr(split[i], ','))
			point = fdf_split(split[i], ',');
		else
		{
			point = &split[i];
			ft_printf("point: %s", point);
		}
		if (point[0][0] == '-' || point[0][0] == '+')
			j++;
		while (point[0][j])
		{
			if (!ft_isdigit(point[0][j]))
				return (false);
			j++;
		}
		ft_free_array(point);
		i++;
	}
	ft_free_array(split);
	free(line);
	return (true);
}

bool	retangular_check(t_map *map)
{
	char	*line;
	int		current_column;

	current_column = 0;
	while((line = get_next_line(map->fd)))
	{
		if (!line)
			return (false);
		map->height++;
		current_column = count_tokens(line, ' ');
		if (map->width== 0)
			map->width= current_column;
		else if ((map->width!= current_column))
		{
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
}

bool	check_extension(char *filename)
{
	if(ft_strnstr(filename, ".fdf", ft_strlen(filename)))
		return (true);
	return (false);
}
