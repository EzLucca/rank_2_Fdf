/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:40:18 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/04 15:22:03 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <fcntl.h>

# define BPP sizeof(int32_t)
# define WIDTH 1280 /* Initial window width */
# define HEIGHT 720 /* Initial window height */
# define TITLE "fdf" /* Text shown in window title bar */
# define MAP_SCALE 0.05 /* Vertical scale of map */

typedef struct s_map
{
	float	map_x;
	float	map_y;
	float	map_z;
	float	color;
} t_map;

typedef struct s_parse
{
	int	file;

} t_parse;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*points;
} t_fdf;

void loop_mlx(t_fdf *fdf);

#endif
