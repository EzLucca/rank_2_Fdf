/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:00:31 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/16 15:07:25 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	fill_color(char *data, t_map *map, int fd)
{
	int	color;

	while (*data == '-')
		data++;
	while (ft_isdigit (*data))
		data++;
	if (*data == ',')
		data++;
	else
		return (0xFFFFFFFF);
	if (ft_strncmp(data, "0X", 2) && ft_strncmp(data, "0x", 2))
		ft_error_map("Invalid_map", fd, map);
	data += 2;
	ft_striteri(data, &ft_upper);
	color = ft_atoi_base(data, "0123456789ABCDEF") << 8 | 0xFF;
	return (color);
}

void	process_points(int fd, t_map *map, char *line, int i)
{
	t_point3d	*point;
	// int			x_offet;
	// int			y_offset;
	int			j;
	char		**split;

	split = ft_split(line, ' ');
	free(line);
	if (!split)
		ft_error_map("split error.", fd, map);
	j = 0;
	// while (split[j])
	// {
	// 	ft_printf("split[%d]: %s\n", j, split[j]); // TESTING: Ok
	// 	j++;
	// }
	// x_offset = (map->cols - 1) * map->interval / 2;
	// y_offset = (map->rows - 1) * map->interval / 2;
	while (j < map->cols)
	{
		point = &(map->grid3d[i][j]);
		point->x = (double)j /* (map->interval) - x_offset*/;
		point->y = (double)i /* (map->interval) - y_offset*/;
		point->z = (double)ft_atoi(split[j]) /* (map->interval)*/;
		printf("x: %f y: %f z: %f\n", point->x, point->y, point->z); // TESTING:
		map->high = ft_max(map->high, point->z);
		map->low = ft_min(map->low, point->z);
		point->mapcolor = fill_color(split[j], map, fd);
		printf("z: %f color: %d\n", point->z, point->mapcolor);
		j++;
	}
	ft_free_array(split);
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
	char	*tmp;
	// char	**split;
	int		y;

	y = 0;
	while (y < map->rows)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			ft_error_map("Gnl error.", fd, map);
		line = ft_strtrim(tmp,"\n");
		free(tmp);
		if (!line)
			ft_error_map("ft_strtrim error.", fd, map);
		// ft_printf("line: %s\n", line); // TESTING: OK
		process_points(fd, map, line, y);
		y++;
	}
	ft_printf("parse_map\n"); // TESTING:
}

void	allocate_grid(t_map *map)
{
	int	i;

	map->grid3d = malloc(sizeof(t_point3d *) * map->rows);
	map->grid2d = malloc(sizeof(t_point2d *) * map->rows);
	// printf("rows: %d\n", map->rows); // TESTING:
	if (!(map->grid2d) || !(map->grid3d))
	{
		free_map(map);
		ft_error("Error malloc grid.");
	}
	i = -1;
	while (++i < map->rows)
	{
		map->grid3d[i] = malloc(sizeof(t_point3d *) * map->cols);
		map->grid2d[i] = malloc(sizeof(t_point2d *) * map->cols);
		// printf("cols: %d\n", map->cols); // TESTING:
		if (!(map->grid2d[i]) || !(map->grid3d[i]))
		{
			if (i + 1 < map->rows)
			{
				map->grid2d[i + 1] = NULL;
				map->grid3d[i + 1] = NULL;
			}
			free_map(map);
			ft_error("Error malloc grid.");
		}
	}
	ft_printf("allocate_grid\n"); // TESTING:
}
