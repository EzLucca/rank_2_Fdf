/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:00:31 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/10 18:24:44 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// void	allocate_memory(t_map *map)
// {
// 	int i;
//
// 	i = 0;
// 	map.points = malloc(sizeof(t_point *) * map.height);
// 	while(i < map.height)
// 	{
// 		map.points[i] = malloc(sizeof(t_point) * map.width);
// 		i++;
// 	}
// }

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

void	parse_map(char *argv, t_map *map)
{
	char	*line;
	char	**split;
	char	**point_parts;
	int		y;
	int		x;
	t_point *p;

	y = 0;
	x = 0;
	ft_bzero(&p, sizeof(t_point));
	map->fd = open(argv, O_RDONLY);
	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		return ;
	while ((line = get_next_line(map->fd)) && y < map->height)
	{
		remove_newline(line);
		split = fdf_split(line, ' ');
		if (!split)
			return (free(line));
		map->points[y] = malloc(sizeof(t_point) * map->width);
		if (!map->points[y])
			return (ft_free_array(split), free(line));
		while (x < map->width)
		{
			t_point *p = &map->points[y][x];
			p->x = x;
			p->y = y;
			if (ft_strchr(split[x], ','))
			{
				point_parts = fdf_split(split[x], ',');
				p->z = ft_atoi(point_parts[0]);
				p->color = ft_atoi_hex(point_parts[1]);
				ft_free_array(point_parts);
			}
			else
			{
				p->z = ft_atoi(split[x]);
				p->color = 0xFFFFFF;
			}
			x++;
		}
		ft_free_array(split);
		free(line);
		y++;
	}
	close(map->fd);
	return ;
}
