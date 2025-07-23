/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:00:31 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/23 10:51:16 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	fill_color(char *data, t_map *map, int fd)
{
	char	*comma;
	int		color;

	comma = ft_strchr(data, ',');
	if (!comma)
		return (0xFFFFFFFF);
	comma++;
	if (ft_strncmp(comma, "0x", 2) && ft_strncmp(comma, "0X", 2))
		ft_error_map("Invalid_map (missing 0x color prefix)", fd, map);
	comma += 2;
	ft_striteri(comma, &ft_upper);
	color = ft_atoi_base(comma, "0123456789ABCDEF") << 8 | 0xFF;
	return (color);
}

static void	process_points(int fd, t_map *map, char *line, int y)
{
	int			x;
	int			x_offset;
	int			y_offset;
	char		**split;

	x = 0;
	split = ft_split(line, ' ');
	free(line);
	if (!split)
		ft_error_map("split error.", fd, map);
	x_offset = (map->cols - 1) * map->interval / 2;
	y_offset = (map->rows - 1) * map->interval / 2;
	while (x < map->cols)
	{
		map->grid3d[y][x].x = (double)x * (map->interval) - x_offset;
		map->grid3d[y][x].y = (double)y * (map->interval) - y_offset;
		map->grid3d[y][x].z = (double)ft_atoi(split[x]) * (map->interval);
		map->grid3d[y][x].mapcolor = fill_color(split[x], map, fd);
		map->high = ft_max(map->high, map->grid3d[y][x].z);
		map->low = ft_min(map->low, map->grid3d[y][x].z);
		x++;
	}
	ft_free_array(split);
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
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
		process_points(fd, map, line, y);
		y++;
	}
}

void	allocate_grid(t_map *map)
{
	int	i;

	map->grid3d = malloc(sizeof(t_point3d *) * map->rows);
	map->grid2d = malloc(sizeof(t_point2d *) * map->rows);
	if (!(map->grid3d) || !(map->grid2d))
	{
		free_map(map);
		ft_error("Error malloc grid.");
	}
	i = 0;
	while (i < map->rows)
	{
		map->grid3d[i] = malloc(sizeof(t_point3d) * map->cols);
		map->grid2d[i] = malloc(sizeof(t_point2d) * map->cols);
		if (!(map->grid3d[i]) || !(map->grid2d[i]))
		{
			free_map(map);
			ft_error("Error malloc grid.");
		}
		i++;
	}
}
