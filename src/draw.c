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

void project_point(t_point *p, t_camera cam)
{
	float x = p->x;
	float y = p->y;
	float z = p->z * cam.z_scale;

	if (cam.projection == 0)
	{
		p->x = (int)((x - y) * cos(cam.angle_z) * cam.zoom) + cam.x_offset;
		p->y = (int)((x + y) * sin(cam.angle_z) - z) * cam.zoom + cam.y_offset;
	}
	else if (cam.projection == 1)
	{
		p->x = x * cam.zoom + cam.x_offset;
		p->y = y * cam.zoom + cam.y_offset - z;
	}
}

static	void draw_line(mlx_image_t *img, t_point a, t_point b, uint32_t color)
{
	int dx;
	int dy;
	int sx = a.x < b.x ? 1 : -1;
	int sy = a.y < b.y ? 1 : -1;
	int err;
	int e2;

	dx = abs(b.x - a.x);
	dy = -abs(b.y - a.y);
	err = dx + dy;
	while (true)
	{
		mlx_put_pixel(img, a.x, a.y, color);
		if (a.x == b.x && a.y == b.y)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			a.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			a.y += sy;
		}
	}
}

void draw_map(t_map *map)
{
	int		i;
	int		j;
	t_point	a;
	t_point	b;

	i = 0;
	while ( i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			a = map->points[i][j];
			// ft_printf("points[i][j]: %d\n", map->points[i][j]); //DEBUG
			project_point(&a, map->camera);
			if (j < map->width - 1)
			{
				b = map->points[i][j + 1];
				project_point(&b, map->camera);
				draw_line(map->img, a, b, a.color);
			}
			if (i < map->height - 1)
			{
				b = map->points[i + 1][j];
				project_point(&b, map->camera);
				draw_line(map->img, a, b, a.color);
			}
			j++;
		}
		i++;
	}
}
