/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:11:00 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/25 13:36:23 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_draw	bresenham_init(t_point2d a, t_point2d b)
{
	t_draw	jack;

	jack.dx = fabs(b.x - a.x);
	jack.dy = -fabs(b.y - a.y);
	if (a.x < b.x)
		jack.sx = 1;
	else
		jack.sx = -1;
	if (a.y < b.y)
		jack.sy = 1;
	else
		jack.sy = -1;
	jack.err = jack.dx + jack.dy;
	jack.cur = a;
	jack.b = b;
	jack.a = a;
	return (jack);
}

static void	bresenham_draw(mlx_image_t *image, t_point2d a, t_point2d b)
{
	int		e2;
	t_draw	jack;

	jack = bresenham_init(a, b);
	while (1)
	{
		if ((uint32_t)jack.cur.x < image->width
			&& (uint32_t)jack.cur.y < image->height)
			mlx_put_pixel(image, jack.cur.x, jack.cur.y,
				get_color(jack.cur, jack.a, jack.b));
		if (jack.cur.x == jack.b.x && jack.cur.y == jack.b.y)
			break ;
		e2 = 2 * jack.err;
		if (e2 >= jack.dy)
		{
			jack.err += jack.dy;
			jack.cur.x += jack.sx;
		}
		if (e2 <= jack.dx)
		{
			jack.err += jack.dx;
			jack.cur.y += jack.sy;
		}
	}
}

static void	project_point(t_map *map, int y, int x)
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
	new->x = (int)((tmp.x * map->zoom - tmp.y * map->zoom)
			* cos(map->alpha) + map->x_offset);
	new->y = (int)(-tmp.z * map->zoom + (tmp.x * map->zoom + tmp.y * map->zoom)
			* sin(map->beta) + map->y_offset);
	if (map->orthogonal == true)
	{
		new->x = (int)(tmp.x * map->zoom + map->x_offset);
		new->y = (int)(tmp.y * map->zoom + map->y_offset);
	}
	if (map->use_zcolor)
		new->rgba = previous->zcolor;
	else
		new->rgba = previous->mapcolor;
}

static void	draw_line(t_fdf *fdf, int x, int y)
{
	if (y == 0 && x == 0)
		project_point(fdf->map, y, x);
	if (y + 1 < fdf->map->rows)
	{
		project_point(fdf->map, y + 1, x);
		bresenham_draw(fdf->image, fdf->map->grid2d[y][x],
			fdf->map->grid2d[y + 1][x]);
	}
	if (x + 1 < fdf->map->cols)
	{
		if (y == 0)
			project_point(fdf->map, y, x + 1);
		bresenham_draw(fdf->image, fdf->map->grid2d[y][x],
			fdf->map->grid2d[y][x + 1]);
	}
}

void	draw_image(void *param)
{
	int		i;
	int		j;
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	reset_draw(fdf->image);
	i = 0;
	while (i < fdf->map->rows)
	{
		j = 0;
		while (j < fdf->map->cols)
		{
			draw_line(fdf, j, i);
			j++;
		}
		i++;
	}
}
