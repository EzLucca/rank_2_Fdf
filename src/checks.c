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

bool	retangular_check(t_map *map)
{
	char	*line;
	char	**split;
	int		current_column;

	current_column = 0;
	while((line = get_next_line(map->fd)))
	{
		if (!line)
			return (false);
		map->height++;
		current_column = count_tokens(line, ' ');
		split = fdf_split(line, ' ');
		if (map->width== 0)
			map->width= current_column;
		else if ((map->width!= current_column))
		{
			free(line);
			ft_free_array(split);
			return (false);
		}
		free(line);
		ft_free_array(split);
	}
	return (true);
}

bool	check_extension(char *filename)
{
	if(ft_strnstr(filename, ".fdf", ft_strlen(filename)))
		return (true);
	return (false);
}
