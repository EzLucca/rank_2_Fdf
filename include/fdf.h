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

# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define BPP sizeof(int32_t)
# define WIDTH 1280 /* Initial window width */
# define HEIGHT 720 /* Initial window height */
# define TITLE "fdf" /* Text shown in window title bar */
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
	double			x_offset;
	double			y_offset;
	double			interval;
	double			alpha;
	double			beta;
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

bool	points_check(char *line);
int		ft_atoi_hex(const char *hex);
void	fill_point(t_point *p, char *data, int x, int y);
void	parse_map(char *argv, t_map *map);
void	loop_mlx(t_map *fdf);
void	project_all_points(t_map *map);
void	draw_map(t_map *map);
void	*free_array(char **array);
void	clear_image(mlx_image_t *img);
void	ft_hook_movement(void *param);

int		process_line(int fd, t_map *map, char *line);
char	remove_newline(char *line);
void	grid_check(int fd, t_map *map);
t_fdf	*init_fdf(char *filename);
t_map	*open_validate_map(char *filename);
void	ft_free_tab(void **tab, size_t len);
void	free_map(t_map *map);
void	ft_error_close(char *str, int fd);
void	ft_error(char *str);
int		check_extension(char *filename);
#endif
