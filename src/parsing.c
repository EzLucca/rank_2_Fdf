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

int ft_atoi_hex(const char *hex)
{
	int result = 0;

	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		hex += 2;
	while (*hex)
	{
		result *= 16;
		if (*hex >= '0' && *hex <= '9')
			result += *hex - '0';
		else if (*hex >= 'a' && *hex <= 'f')
			result += *hex - 'a' + 10;
		else if (*hex >= 'A' && *hex <= 'F')
			result += *hex - 'A' + 10;
		hex++;
	}
	return result;
}

int	fill_color(char *data, t_map *map, int fd)
{
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
	// ft_printf("data: %s\n", data); // TESTING:
	return (ft_atoi_hex(data));
}

int	process_line(int fd, t_map *map, char *line, int y)
{
	char		**split;
	t_point3d	*point;
	int			x_offset;
	int			y_offset;
	int			x;

	split = ft_split(line, ' ');
	if (!split)
		return (free(line), 0); // TODO:
	x = 0;
	while (split[x])
	{
		point = &(map->grid3d[y][x]);
		x_offset = (map->cols - 1) * map->interval / 2;
		y_offset = (map->rows - 1) * map->interval / 2;
		point->x = (double)x * (map->interval) - x_offset; 
		point->y = (double)y * (map->interval) - y_offset; 
		point->z = (double)ft_atoi(split[x]) * (map->interval); 
		map->high = ft_max(map->high, point->z);
		map->low = ft_min(map->low, point->z);
		point->mapcolor = fill_color(split[x], map, fd);
		// ft_printf("split[%d] = %s, y: %d\n", x, split[x], y);  // TESTING:
		// ft_printf("x_offset: %d y_offset: %d\n", x_offset, y_offset); // TESTING: 
		// ft_printf("x: %d y: %d z: %d\n", point->x, point->y, point->z); // TESTING:
		// ft_printf("high: %d low: %d\n", map->high, map->low); // TESTING:
		// ft_printf("mapcolor: %d\n", point->mapcolor); // TESTING:
		x++;
	}
	ft_free_array(split);
	free(line);
	return (x);
}

void	parse_map(char *filename, t_map *map)
{
	char	*line;
	char	*tmp;
	int		y;
	int		fd;

	y = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	while (y < map->rows)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			ft_error_map("Gnl error.", fd, map);
		line = ft_strtrim(tmp,"\n");
		// ft_printf("line: %s\n", line); // TESTING:
		if (!line)
			ft_error_map("Ft_strtrim error.", fd, map);
		free(tmp);
		if(!process_line(fd, map, line, y))
			break ; // FIXIT:
		y++;
	}
	close (fd);
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
		map->grid3d[i] = malloc(sizeof(t_point3d *) * map->rows);
		map->grid2d[i] = malloc(sizeof(t_point2d *) * map->rows);
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
