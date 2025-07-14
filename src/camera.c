/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:11:29 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 17:13:53 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init_camera(t_camera *camera, t_map *map)
{
	camera->zoom = fmin(WIDTH / map->width / 2, HEIGHT / map->height / 2);
	camera->x_offset = WIDTH / 2;
	camera->y_offset = HEIGHT / 2;
	camera->z_scale = 1;
	camera->angle_x = 0.5;
	camera->angle_y = 0.5;
	camera->angle_z = 0.5;
	camera->projection = 0; // 0 = isometric
}

void	hook_rotation(t_map *img)
{
	if (mlx_is_key_down(img->mlx, MLX_KEY_J))
		img->camera.angle_z += 1;
	else if (mlx_is_key_down(img->mlx, MLX_KEY_L))
		img->camera.angle_z -= 1;
	if (mlx_is_key_down(img->mlx, MLX_KEY_I))
		img->camera.angle_x += 1;
	else if (mlx_is_key_down(img->mlx, MLX_KEY_K))
		img->camera.angle_x -= 1;
	if (mlx_is_key_down(img->mlx, MLX_KEY_Y))
		img->camera.angle_y -= 1;
	else if (mlx_is_key_down(img->mlx, MLX_KEY_H))
		img->camera.angle_y += 1;
}

void	ft_hook_movement(void *param)
{
	t_map *img;

	img = param;
	if (mlx_is_key_down(img->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(img->mlx);
	// if (mlx_is_key_down(img->mlx, MLX_KEY_A))
	// 	img->camera.angle_x -= 10;
	else if (mlx_is_key_down(img->mlx, MLX_KEY_D))
		img->camera.angle_x += 10;
	if (mlx_is_key_down(img->mlx, MLX_KEY_W))
		img->camera.angle_y -= 10;
	else if (mlx_is_key_down(img->mlx, MLX_KEY_S))
		img->camera.angle_y += 10;
	if (mlx_is_key_down(img->mlx, MLX_KEY_Z) && img->camera.angle_z > -0.5)
		img->camera.angle_z -= 0.01;
	else if (mlx_is_key_down(img->mlx, MLX_KEY_X) && img->camera.angle_z < 0.5)
		img->camera.angle_z += 0.01;
	// if (mlx_is_key_down(img->mlx, MLX_KEY_M))
	// 	img->height = YELLOW;
	// else if (mlx_is_key_down(img->mlx, MLX_KEY_N))
	// 	img->height = MAGENTA;
	hook_rotation(img);
}
