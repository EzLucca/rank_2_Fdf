/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:11:00 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/16 14:44:01 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	bresenham_algo(mlx_image_t *image, t_point2d a, t_point2d b)
{
	int			error[2];
	t_point2d	cur;

	cur.x = a.x;
	cur.y = a.y;
	error[0] = abs(b.x - a.x) - abs(b.y - a.y);
	while (cur.x != b.x || cur.y != b.y)
	{
		if ((uint32_t)cur.x < image->width && (uint32_t)cur.y < image->height)
			mlx_put_pixel(image, cur.x, cur.y, get_color(cur, a, b));
		error[1] = 2 * error[0];
		if (error[1] > -abs(b.y - a.y))
		{
			error[0] -= abs(b.y - a.y);
			cur.x += (a.x < b.x);
			cur.x -= (b.x < a.x);
		}
		if (error[1] > -abs(b.x - a.x))
		{
			error[0] -= abs(b.x - a.x);
			cur.y += (a.y < b.y);
			cur.y -= (b.y < a.y);
		}
	}
}

void	project_point(t_map *map, int y, int x)
{
	t_point3d	*previous;
	t_point3d	tmp;
	t_point2d	*new;

	previous = &(map->grid3d[y][x]);
	new = &(map->grid2d[y][x]);
	tmp.x = previous->x;
	tmp.y = previous->y;
	tmp.z = previous->z * map->zscale;
	rotate_z(&tmp.x, &tmp.y, map->zrotate);
	rotate_x(&tmp.y, &tmp.z, map->xrotate);
	rotate_y(&tmp.x, &tmp.z, map->yrotate);
	new->x = (int)((tmp.x * map->zoom - tmp.y * map->zoom) * cos(map->alpha) + map->x_offset);
	new->y = (int)(-tmp.z * map->zoom + (tmp.x * map->zoom + tmp.y * map->zoom) * sin(map->beta) + map->y_offset);
	if (map->use_zcolor)
		new->rgba = previous->zcolor;
	else
		new->rgba = previous->mapcolor;
}

void	draw_line(t_fdf *fdf, int x, int y)
{
	if (y == 0 && x == 0)
		project_point(fdf->map, y, x);
	if (y + 1 < fdf->map->rows)
	{
		project_point(fdf->map, y + 1, x);
		bresenham_algo(fdf->image, fdf->map->grid2d[y][x], fdf->map->grid2d[y + 1][x]);
	}
	if (x + 1 < fdf->map->cols)
	{
		project_point(fdf->map, y, x + 1);
		bresenham_algo(fdf->image, fdf->map->grid2d[y][x], fdf->map->grid2d[y][x + 1]);
	}
}

void	draw_image(t_fdf *fdf)
{
	int		i;
	int		j;

	reset_draw(fdf->image);
	i = 0;
	while (i < fdf->map->rows)
	{
		j = 0;
		while (j < fdf->map->cols)
			draw_line(fdf, j, i);
	}
}

void	display_menu(mlx_t *mlx)
{
	int		x;
	int		y;

	x = 20;
	y = 20;
	mlx_put_string(mlx, "CONTROLS", x, y);
	mlx_put_string(mlx, "Colour\t\t\t\t\t\t\t\tc", x, y += 35);
	mlx_put_string(mlx, "Zoom\t\t\t\t\t\t\t\t\t\tmouse scroll or -+", x, y += 20);
	mlx_put_string(mlx, "Translate\t\t\t\t\tarrow keys", x, y += 20);
	mlx_put_string(mlx, "Scale z\t\t\t\t\t\t\ts + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate x\t\t\t\t\t\tx + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate y\t\t\t\t\t\tc + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate z\t\t\t\t\t\tz + </>", x, y += 20);
	mlx_put_string(mlx, "PROJECTION", x, y += 30);
	mlx_put_string(mlx, "Angle x\t\t\t\t\t\t\tq + </>", x, y += 25);
	mlx_put_string(mlx, "Angle y\t\t\t\t\t\t\tw + </>", x, y += 20);
	mlx_put_string(mlx, "Isometric\t\t\t\t\t1", x, y += 20);
	mlx_put_string(mlx, "Dimetric\t\t\t\t\t\t2", x, y += 20);
	mlx_put_string(mlx, "Trimetric\t\t\t\t\t3", x, y += 20);
	mlx_put_string(mlx, "RESET\t\t\t\t\t\t\t\t\t0", x, y += 30);
}
