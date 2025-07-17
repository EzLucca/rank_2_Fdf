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

void	process_points(int fd, t_map *map, char **split, int y)
{
	t_point3d	*point;
	int			x_offset;
	int			y_offset;
	int			x;

	x = 0;
	// while(split[x])
	// {
	// 	printf("split[x]: %s\n", split[x]); // TESTING
	// 	x++;
	// }
	// -1,0xFFFFFF 2 3 4 5 6 7 8 9,0xFFFFFF
	while (x < map->cols)
	{
		printf("split[x]: %s x: %d cols: %d\n", split[x], x, map->cols); // TESTING
		point = &(map->grid3d[y][x]);
		x_offset = (map->cols - 1) * map->interval / 2;
		y_offset = (map->rows - 1) * map->interval / 2;
		point->x = (double)x * (map->interval) - x_offset; 
		point->y = (double)y * (map->interval) - y_offset; // BUG:
		point->z = (double)ft_atoi(split[x]) * (map->interval); 
		map->high = ft_max(map->high, point->z);
		map->low = ft_min(map->low, point->z);
		point->mapcolor = fill_color(split[x], map, fd);
		x++;
	}
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
	char	*tmp;
	char	**split;
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
		split = ft_split(line, ' ');
		free(line);
		if (!split)
			return (free(line)); // TODO:
		process_points(fd, map, split, y);
		ft_free_array(split);
		y++;
	}
}

void	allocate_grid(t_map *map)
{
	int	i;

	map->grid3d = malloc(sizeof(t_point3d *) * map->rows);
	map->grid2d = malloc(sizeof(t_point2d *) * map->rows);
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
}
