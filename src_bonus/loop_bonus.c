/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:04:29 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/30 22:37:25 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/fdf_bonus.h"

void	reset_map(t_fdf *fdf)
{
	int	width;
	int	height;
	int	map_width;
	int	map_height;

	width = fdf->mlx->width;
	height = fdf->mlx->height;
	map_width = fdf->map->cols * fdf->map->zoom;
	map_height = fdf->map->rows * fdf->map->zoom;
	fdf->map->alpha = 0.46373398 / 2;
	fdf->map->beta = 0.46373398;
	fdf->map->xrotate = 0;
	fdf->map->yrotate = 0;
	fdf->map->zrotate = 0;
	fdf->map->x_offset = (width / 2) - (map_width / 2);
	fdf->map->y_offset = (height / 2) - (map_height / 2);
	fdf->map->zoom = 1;
	fdf->map->zscale = 1;
	fdf->map->use_zcolor = false;
}

void	display_menu(mlx_t *mlx)
{
	int		x;
	int		y;

	x = 20;
	y = 20;
	mlx_put_string(mlx, "CONTROLS", x, y);
	mlx_put_string(mlx, "Colors\t\t\t\t\t\t\t\tc", x, y += 35);
	mlx_put_string(mlx, "Zoom\t\t\t\t\t\t\t\t\t\tscroll or -+", x, y += 20);
	mlx_put_string(mlx, "Translate\t\t\t\t\tarrow keys", x, y += 20);
	mlx_put_string(mlx, "Scale z\t\t\t\t\t\t\ts + </>", x, y += 20);
	mlx_put_string(mlx, "Angle x\t\t\t\t\t\t\t\tq + </>", x, y += 25);
	mlx_put_string(mlx, "Angle y\t\t\t\t\t\t\t\tw + </>", x, y += 20);
	mlx_put_string(mlx, "ROTATIONS", x, y += 30);
	mlx_put_string(mlx, "Rotate X\t\t\t\t\t\t\t1 + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate Y\t\t\t\t\t\t\t2 + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate Z\t\t\t\t\t\t\t3 + </>", x, y += 20);
	mlx_put_string(mlx, "PROJECTION", x, y += 30);
	mlx_put_string(mlx, "Isometric\t\t\t\t\t\t\ti", x, y += 20);
	mlx_put_string(mlx, "Orthogonal\t\t\t\t\t\to", x, y += 20);
	mlx_put_string(mlx, "RESET\t\t\t\t\t\t\t\t\t\t\t0", x, y += 30);
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

void	loop_handler(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	ft_hook(fdf);
	ft_hook_rotate(fdf);
	ft_hook_project(fdf);
	draw_image(fdf);
}
