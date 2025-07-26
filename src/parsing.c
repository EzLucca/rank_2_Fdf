/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:00:31 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/26 12:08:00 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	fill_color(char *data, t_map *map, int fd, char **split)
{
	char	*comma;
	int		color;

	(void) fd;
	(void) map;
	(void) split;
	comma = ft_strchr(data, ',');
	if (!comma)
		return (0xFFFFFFFF);
	comma += 3;
	ft_striteri(comma, &ft_upper);
	if (ft_strlen(comma) > 6)
	{
		ft_free_array(split);
		ft_error_map("Invalid_map (color must be 6-digit hex)", fd, map);
	}
	color = ft_atoi_base(comma, "0123456789ABCDEF") << 8 | 0xFF;
	return (color);
}

static void	process_points(int fd, t_map *map, char **split, int y)
{
	int			x;
	int			x_offset;
	int			y_offset;

	x = 0;
	x_offset = (map->cols - 1) * map->interval / 2;
	y_offset = (map->rows - 1) * map->interval / 2;
	while (x < map->cols)
	{
		map->grid3d[y][x].x = (double)x * (map->interval) - x_offset;
		map->grid3d[y][x].y = (double)y * (map->interval) - y_offset;
		map->grid3d[y][x].z = (double)ft_atoi(split[x]) * (map->interval);
		if (map->grid3d[y][x].z > 10000 || map->grid3d[y][x].z < -10000)
		{
			ft_free_array(split);
			ft_error_map("Value of point not allowed.", fd, map);
		}
		map->grid3d[y][x].mapcolor = fill_color(split[x], map, fd, split);
		map->high = ft_max(map->high, map->grid3d[y][x].z);
		map->low = ft_min(map->low, map->grid3d[y][x].z);
		x++;
	}
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
	char	**split;
	char	*tmp;
	int		y;

	y = 0;
	while (y < map->rows)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			ft_error_map("Gnl error.", fd, map);
		line = ft_strtrim(tmp, "\n");
		free(tmp);
		split = ft_split(line, ' ');
		free(line);
		if (!split)
			ft_error_map("split error.", fd, map);
		process_points(fd, map, split, y);
		y++;
		ft_free_array(split);
	}
}
