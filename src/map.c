/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:37:46 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/10 17:00:50 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	grid_check(t_map *map)
{
	char	*line;
	int		current_column;

	current_column = 0;
	while((line = get_next_line(map->fd)))
	{
		if (!line)
			ft_error_close("Invalid map.", map);
		remove_newline(line);
		if (!points_check(line))
			ft_error_close("Invalid point.", map);
		map->height++;
		current_column = count_tokens(line, ' ');
		if (map->width== 0)
			map->width= current_column;
		else if ((map->width!= current_column))
		{
			free(line);
			ft_error_close("Couldn't read file", map);
		}
		free(line);
	}
	return ;
}

void	open_validate_map(char *argv, t_map *map)
{
	check_extension(argv);
	map->fd = open(argv, O_RDONLY);
	if (map->fd < 0)
		ft_error_close("Can't open file.", map); //close fd
	grid_check(map);
	close(map->fd);
}
