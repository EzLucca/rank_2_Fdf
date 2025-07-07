/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:40:18 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/07 17:55:09 by edlucca          ###   ########.fr       */
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
	int		map_x;
	int		map_y;
	int		map_z;
	int		color;
} t_map;

typedef struct s_parse
{
	int	file;

} t_parse;

typedef struct s_fdf
{
	int			fd;
	int			height;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*points;
	int			map_x;
	int			map_y;
	int			map_z;
} t_fdf;

void loop_mlx(t_fdf *fdf);
void ft_error(char *str);
void	open_validate_map(char *argv, t_fdf *fdf);
bool	check_extension(char *filename);

#endif
