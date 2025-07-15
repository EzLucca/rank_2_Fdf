/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:00:31 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/15 22:42:38 by edlucca          ###   ########.fr       */
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

void	fill_point(t_point *p, char *data, int x, int y)
{
	char	**point_parts;
	p->x = x;
	p->y = y;
	if (ft_strchr(data, ','))
	{
		point_parts = ft_split(data, ',');
		p->z = ft_atoi(point_parts[0]);
		p->color = ft_atoi_hex(point_parts[1]);
		ft_free_array(point_parts);
	}
	else
	{
		p->z = ft_atoi(data);
		p->color = ft_atoi_hex("0xFFFFFFFF");
	}
	// ft_printf("fill_point: x=%d y=%d z=%d color:%d\n", x, y, p->z, p->color); // DEBUG
}

int	process_line(int fd, t_map *map, char *line)
{
	char	**split;
	char	*tmp;
	int		x;

	tmp = ft_strtrim(line, "\n");
	if (!tmp)
		return (free(line), 0); //TODO:
	free(line);
	split = ft_split(tmp, ' ');
	if (!split)
		return (free(tmp), 0); // TODO:
							   
	map->points[y] = malloc(sizeof(t_point) * map->width);
	if (!map->points[y])
		return (ft_free_array(split), free(line), 0);
	x = 0;
	while (split[x])
	{
		map->high = ft_max(map->high, ft_atoi(split[x]));
		map->low = ft_min(map->low, ft_atoi(split[x]));
		// ft_printf("split[%d] = %s, y: %d\n", x, split[x], y);  // DEBUG
		// fill_point(&map->points[y][x], split[x], x, y);
		x++;
	}
	ft_free_array(split);
	free(line);
	return (x);
}
