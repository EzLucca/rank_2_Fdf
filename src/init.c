/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:56:28 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/26 12:05:31 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init_map(t_map *map)
{
	map->alpha = 20 * (M_PI / 180);
	map->beta = 30 * (M_PI / 180);
	map->xrotate = 0;
	map->yrotate = 0;
	map->zrotate = 0;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->zoom = 1;
	map->zscale = 1;
	map->use_zcolor = false;
	map->high = INT_MIN;
	map->low = INT_MAX;
	map->rows = 0;
	map->cols = 0;
	map->grid2d = NULL;
	map->grid3d = NULL;
	map->orthogonal = false;
}

void	init_fdf(char *filename, t_fdf	*fdf)
{
	fdf->map = open_validate_map(filename);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!fdf->mlx)
	{
		free_map(fdf->map);
		ft_error("Error: fdf.mlx");
	}
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image)
	{
		mlx_close_window(fdf->mlx);
		mlx_terminate (fdf->mlx);
		free_map(fdf->map);
		ft_error("Error: fdf.image");
	}
}

void	allocate_grid(t_map *map)
{
	int	i;

	map->grid3d = malloc(sizeof(t_point3d *) * map->rows);
	map->grid2d = malloc(sizeof(t_point2d *) * map->rows);
	if (!(map->grid3d) || !(map->grid2d))
	{
		free_map(map);
		ft_error("Error malloc grid.");
	}
	i = 0;
	while (i < map->rows)
	{
		map->grid3d[i] = malloc(sizeof(t_point3d) * map->cols);
		map->grid2d[i] = malloc(sizeof(t_point2d) * map->cols);
		if (!(map->grid3d[i]) || !(map->grid2d[i]))
		{
			free_map(map);
			ft_error("Error malloc grid.");
		}
		i++;
	}
}
