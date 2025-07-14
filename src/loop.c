/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:04:29 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 17:25:22 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void render(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	draw_map(map);
}

static void key_hook(mlx_key_data_t key, void *param)
{
	t_map *	fdf;

	fdf = (t_map*) param;
	if (key.action == MLX_PRESS)
	{
		if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(fdf->mlx);
	}
}

static void resize_hook(int width, int height, void *param)
{
	t_map	*fdf;
	float	map_width;
	float	map_height;

	fdf = (t_map*) param;
	if(fdf->img)
		mlx_delete_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, width, height);
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
	map_width = fdf->width * fdf->camera.zoom;
	map_height = fdf->height * fdf->camera.zoom;
	fdf->camera.x_offset = (width / 2) - (map_width / 2);
	fdf->camera.y_offset = (height / 2) - (map_height / 2);
}

void loop_mlx(t_map *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (fdf->mlx != NULL)
	{
		fdf->img = mlx_new_image(fdf->mlx, fdf->mlx->width, fdf->mlx->height);
		if (fdf->img != NULL)
		{
			if(mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) != -1)
			{
				mlx_loop_hook(fdf->mlx, &ft_hook_movement, fdf);
				mlx_key_hook(fdf->mlx, key_hook, fdf);
				mlx_loop_hook(fdf->mlx, &render, fdf);
				mlx_resize_hook(fdf->mlx, resize_hook, fdf);
				// mlx_scroll_hook(fdf->mlx, scroll_hook, fdf);
				// if (mlx_loop_hook(fdf->mlx, loop_hook, fdf))
				mlx_loop(fdf->mlx);
			}
		}
		mlx_delete_image(fdf->mlx, fdf->img);
	}
	mlx_terminate(fdf->mlx);
}
