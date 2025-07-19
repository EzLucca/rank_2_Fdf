/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:40:18 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/16 14:48:16 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define BPP sizeof(int32_t)
# define WIDTH 1280 /* Initial window width */
# define HEIGHT 720 /* Initial window height */
# define TITLE "Fdf" /* Text shown in window title bar */
# define TEXT_COLOR			0xEAEAEAFF
# define BACKGROUND			0x22222200
# define MENU_BACKGROUND	0x1E1E1EFF
# define COLOR_TEN			0x9e0142ff
# define COLOR_NINE			0xd53e4fff
# define COLOR_EIGHT		0xf46d43ff
# define COLOR_SEVEN		0xfdae61ff
# define COLOR_SIX			0xfee08bff
# define COLOR_FIVE			0xe6f598ff
# define COLOR_FOUR			0xabdda4ff
# define COLOR_THREE		0x66c2a5ff
# define COLOR_TWO			0x3288bdff
# define COLOR_ONE			0x5e4fa2ff

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
	int		zcolor;
} t_point3d;

typedef struct s_point2d
{
	int		x;
	int		y;
	int		z;
	int		rgba;
} t_point2d;

typedef struct s_map
{
	int				rows;
	int				cols;
	int				high;
	int				low;
	bool			use_zcolor;
	double			alpha;
	double			beta;
	double			interval;
	double			x_offset;
	double			y_offset;
	double			xrotate;
	double			yrotate;
	double			zrotate;
	double			zoom;
	double			zscale;
	t_point3d		**grid3d;
	t_point2d		**grid2d;
} t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*image;
} t_fdf;

void	*free_array(char **array);

// rotations.c
void	rotate_x(double *y, double *z, double alpha);
void	rotate_y(double *x, double *z, double beta);
void	rotate_z(double *x, double *y, double gamma);

// parsing.c
int		ft_atoi_hex(const char *hex);
int		fill_color(char *data, t_map *map, int fd);
void	process_points(int fd, t_map *map, char *line, int y);
void	parse_map(int fd, t_map *map);
void	allocate_grid(t_map *map);

// main.c
void	grid_check(int fd, t_map *map);
void	init_map(t_map *map);
t_map	*open_validate_map(char *filename);
void	init_fdf(char *filename, t_fdf *fdf);

// checks.c
bool	color_check(const char *color);
bool	number_check(const char *str);
bool	valid_point(char *token);
bool	points_check(char *line);

// image.c
int		radiant(int begin, int end, double percent);
int		get_color(t_point2d current, t_point2d a, t_point2d b);
double	colormix(int begin, int end, int current);
int		colors(double percent);
void	set_zcolor(t_map *map);

// hook.c
void	ft_hook_project(void *param);
void	ft_hook_rotate(void *param);
void	ft_hook(void *param);
void	ft_scroll_hook(double xdelta, double ydelta, void *param);
void	resize_hook(int width, int height, void *param);

// loop.c
void	loop_mlx(t_fdf *fdf);
void	reset_map(t_map *map);
void	reset_draw(mlx_image_t *image);

// draw.c
void	bresenham_algo(mlx_image_t *image, t_point2d a, t_point2d b);
void	project_point(t_map *map, int y, int x);
void	draw_line(t_fdf *fdf, int x, int y);
void	draw_image(void *param);
void	display_menu(mlx_t *mlx);

// utils.c
void	ft_error(char *str);
void	ft_free_tab(void **tab, size_t len);
void	free_map(t_map *map);
void	ft_error_close(char *str, int fd);
void	ft_error_map(char *str, int fd, t_map *map);
void	ft_upper(unsigned int i, char *c);
// int		check_extension(char *filename);
#endif
