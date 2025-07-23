/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:11:16 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/23 19:10:55 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fdf		*fdf;

	fdf = (t_fdf *)param;
	if (ydelta > 0)
		fdf->map->zoom *= 1.02;
	else if (ydelta < 0 && fdf->map->zoom * 0.98 > 0)
		fdf->map->zoom *= 0.98;
	xdelta++;
}

void	ft_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_0))
		reset_map(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->map->x_offset -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->map->x_offset += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->map->y_offset += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->map->y_offset -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		ft_scroll_hook(0, 1, param);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		ft_scroll_hook(0, -1, param);
}

void	ft_hook_rotate(void *param)
{
	t_fdf	*fdf;
	double	sign;

	fdf = (t_fdf *) param;
	sign = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_COMMA))
		sign = -1;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_PERIOD))
		sign = 1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->map->alpha += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->map->beta += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->map->zscale += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		fdf->map->xrotate += sign * 0.02f;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
		fdf->map->yrotate += sign * 0.02f;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3))
		fdf->map->zrotate += sign * 0.02f;
}

void	ft_hook_project(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_C))
		fdf->map->use_zcolor = !(fdf->map->use_zcolor);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_O))
		fdf->map->orthogonal = true;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
		fdf->map->orthogonal = false;
}

void	resize_hook(int width, int height, void *param)
{
	t_fdf	*fdf;
	float	map_width;
	float	map_height;

	fdf = (t_fdf *) param;
	if (fdf->image)
		mlx_delete_image(fdf->mlx, fdf->image);
	fdf->image = mlx_new_image(fdf->mlx, width, height);
	mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
	map_width = fdf->map->cols * fdf->map->zoom;
	map_height = fdf->map->rows * fdf->map->zoom;
	fdf->map->x_offset = (width / 2) - (map_width / 2);
	fdf->map->y_offset = (height / 2) - (map_height / 2);
}
