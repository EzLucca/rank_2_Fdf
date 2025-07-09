/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:40:18 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 17:25:19 by edlucca          ###   ########.fr       */
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

typedef struct s_point/* Represent the 3d point */
{
	int		x;
	int		y;
	int		z;
	int		color;
} t_point;

typedef struct s_map
{
	int			fd;                 /* file descriptor */
	int			height;				/* Number of lines */	
	int			width;				/* Number of columns */
	mlx_t		*mlx;				/* init the mlx42 */
	mlx_image_t	*img;				/* Store the image */
	t_point		**points;			/* 2d array of points */
} t_map;

typedef struct s_camera
{
	double	zoom;
	double	angle_x;
	double	angle_y;
	double	angle_z;
	int		x_offset;
	int		y_offset;
	double	z_scale;
	int		projection; // 0 = isometric, 1 = parallel, etc.
}	t_camera;

typedef struct s_image
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		image;
	t_map		map;
	t_camera	camera;
}	t_fdf;

typedef struct s_draw
{
	t_point	start;
	t_point	end;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}	t_draw;


void	loop_mlx(t_map *fdf);
void	ft_error(char *str);
void	open_validate_map(char *argv, t_map *fdf);
bool	check_extension(char *filename);
bool	retangular_check(t_map *map);
char	**fdf_split(char const *s, char c);
int		count_tokens(const char *s, char c);
void	ft_error_close(char *str, t_map *map);
bool	points_check(t_map *map);

void	read_map(char *filename, t_map *map);
void	draw(t_fdf *fdf);
void	setup_hooks(t_fdf *fdf);
void	project_point(t_point *p, t_fdf *fdf);
void	put_pixel(t_image *img, int x, int y, int color);
void	clear_image(t_image *img);
void	update_image(t_fdf *fdf);
void	init_camera(t_camera *camera, t_map *map);
#endif
