/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:40:18 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/10 18:23:49 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define BPP sizeof(int32_t)
# define WIDTH 1280 /* Initial window width */
# define HEIGHT 720 /* Initial window height */
# define TITLE "fdf" /* Text shown in window title bar */
# define MAP_SCALE 0.05 /* Vertical scale of map */
# define ISO_ANGLE 0.523599

typedef struct s_point/* Represent the 3d point */
{
	int		x;
	int		y;
	int		z;
	int		color;
} t_point;

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

typedef struct s_map
{
	int			fd;                 /* file descriptor */
	int			height;				/* Number of lines */	
	int			width;				/* Number of columns */
	int			zoom;
	mlx_t		*mlx;				/* init the mlx42 */
	mlx_image_t	*img;				/* Store the image */
	t_point		**points;			/* 2d array of points */
	float		elev_scale;
	t_camera	camera;
} t_map;


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


bool	points_check(char *line);
// char	**fdf_split(char const *s, char c);
// int		count_tokens(const char *s, char c);
int		ft_atoi_hex(const char *hex);
int		process_line(t_map *map, char *line, int y);
void	fill_point(t_point *p, char *data, int x, int y);
void	parse_map(char *argv, t_map *map);
void	loop_mlx(t_map *fdf);
void	open_validate_map(char *argv, t_map *fdf);
void	check_extension(char *filename);
void	grid_check(t_map *map);
void	remove_newline(char *line);
void	project_all_points(t_map *map);
void	draw_line(t_point a, t_point b, mlx_image_t *img);
void	draw_map_lines(t_map *map);
void	ft_error(char *str);
void	ft_error_close(char *str, t_map *map);
void	*free_array(char **array);
t_point	project_point(t_point p, t_map *map);
void	clear_image(mlx_image_t *img);

void	read_map(char *filename, t_map *map);
void	draw(t_fdf *fdf);
void	setup_hooks(t_fdf *fdf);
void	put_pixel(t_image *img, int x, int y, int color);
void	update_image(t_fdf *fdf);
void	init_camera(t_camera *camera, t_map *map);
#endif
