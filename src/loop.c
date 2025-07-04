/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:04:29 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/04 15:04:55 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void key_hook(mlx_key_data_t key, void *param)
{
	t_fdf *	fdf;

	fdf = (t_fdf*) param;
	if (key.action == MLX_PRESS)
	{
		if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(fdf->mlx);
	}
}

static void resize_hook(int width, int height, void *param)
{
	t_fdf	*fdf;
	fdf = (t_fdf*) param;

	mlx_resize_image(fdf->img, width, height);
}

void loop_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (fdf->mlx != NULL)
	{
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		if (fdf->img != NULL)
		{
			if(mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) != -1)
			{
				mlx_key_hook(fdf->mlx, key_hook, fdf);
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

