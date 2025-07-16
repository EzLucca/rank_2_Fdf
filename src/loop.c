/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:04:29 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/16 16:05:30 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


void	reset_map(t_map *map)
{
	map->alpha = 0.46373398 / 2;
	map->beta = 0.46373398;
	map->xrotate = 0;
	map->yrotate = 0;
	map->zrotate = 0;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->zoom = 1;
	map->zscale = 1;
	map->use_zcolor = false;
}

void	reset_draw(mlx_image_t *image)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
		{
			mlx_put_pixel(image, j, i, BACKGROUND);
			j++;
		}
		i++;
	}
}

// void	loop_mlx(t_fdf *fdf)
// {
// 	if(mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
// 	{
// 		free_map(fdf->map);
// 		mlx_close_window(fdf->mlx);
// 		// ft_error(mlx_strerror(mlx_errno));
// 		ft_error("error image");
// 	}
// 	mlx_loop_hook(fdf->mlx, &ft_hook, fdf);
// 	mlx_loop_hook(fdf->mlx, &ft_hook_rotate, fdf);
// 	mlx_loop_hook(fdf->mlx, &ft_hook_project, fdf);
// 	mlx_scroll_hook(fdf->mlx, &ft_scroll_hook, fdf);
// 	mlx_loop(fdf->mlx);
// 	mlx_delete_image(fdf->mlx, fdf->image);
// 	mlx_terminate(fdf->mlx);
// }
