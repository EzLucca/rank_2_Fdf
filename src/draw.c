/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:11:00 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 17:13:16 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_line(t_point a, t_point b, mlx_image_t *img)
{
	int dx = abs(b.x - a.x);
	int dy = -abs(b.y - a.y);
	int sx = a.x < b.x ? 1 : -1;
	int sy = a.y < b.y ? 1 : -1;
	int err = dx + dy;

	int x = a.x;
	int y = a.y;

	while (1)
	{
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
			mlx_put_pixel(img, x, y, a.color);
		if (x == b.x && y == b.y)
			break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y += sy;
		}
	}
}

void draw_map_lines(t_map *map)
{
	int row;
	int col;

	row = 0;
	col = 0;
	while ( row < map->height)
	{
		while (col < map->width)
        {
            if (col + 1 < map->width)
                draw_line(map->points[row][col], map->points[row][col + 1], map->img);
            if (row + 1 < map->height)
                draw_line(map->points[row][col], map->points[row + 1][col], map->img);
        }
    }
}

t_point project_point(t_point p, t_map *map)
{
	float angle = ISO_ANGLE;
	int zoom = map->zoom;
	float elev_scale = map->elev_scale;

	t_point projected;

	p.x *= zoom;
	p.y *= zoom;
	p.z *= elev_scale;

	projected.x = (p.x - p.y) * cos(angle);
	projected.y = (p.x + p.y) * sin(angle) - p.z;
	projected.color = p.color;

	return projected;
}

void	project_all_points(t_map *map)
{
	int row;
	int col;

	row = 0;
	col = 0;
	while ( row < map->height)
	{
		while (col < map->width)
		{
			map->points[row][col] = project_point(map->points[row][col], map);
			col++;
		}
		row++;
	}
}
