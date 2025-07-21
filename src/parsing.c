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

void	process_points(int fd, t_map *map, char *line, int y)
{
	int			x;
	char		**split;

	x = 0;
	split = ft_split(line, ' ');
	free(line);
	if (!split)
		ft_error_map("split error.", fd, map);
	while (x < map->cols)
	{
		map->grid3d[y][x].x = (double)x;
		map->grid3d[y][x].y = (double)y;
		map->grid3d[y][x].z = (double)ft_atoi(split[x]);
		map->grid3d[y][x].mapcolor = fill_color(split[x], map, fd);
		map->high = ft_max(map->high, map->grid3d[y][x].z);
		map->low = ft_min(map->low, map->grid3d[y][x].z);
		// printf("x: %f y: %f z: %f color: %d\n", map->grid3d[y][x].x, map->grid3d[y][x].y, map->grid3d[y][x].z, map->grid3d[y][x].mapcolor); // TESTING:
		// printf("z: %f color: %d\n", point->z, point->mapcolor);
		x++;
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
		// ft_printf("line: %s\n", line); // TESTING: OK
		process_points(fd, map, line, y);
		// for (int i = 0; i < map->rows; i++)
		// {
		// 	for (int j = 0; j < map->cols; j++)
		// 	{
		// 		ft_printf("map->x: %d, map->y: %d, map->z: %d\n",
		// 				map->grid3d[i][j].x,
		// 				map->grid3d[i][j].y,
		// 				map->grid3d[i][j].z);
		// 	}
		// }
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
