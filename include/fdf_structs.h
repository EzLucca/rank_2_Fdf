/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:27:30 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/26 13:58:38 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCTS_H
# define FDF_STRUCTS_H

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
	int		zcolor;
}	t_point3d;

typedef struct s_point2d
{
	double	x;
	double	y;
	double	z;
	int		rgba;
}	t_point2d;

typedef struct s_draw
{
	int			dx;		// Difference in x between a and b (b.x - a.x)
	int			dy;		// Difference in y between a and b (b.y - a.y)
	int			sx;		// Direction for x: +1 if a.x < b.x, -1 if a.x > b.x
	int			sy;		// Direction for y: +1 if a.y < b.y, -1 if a.y > b.y
	int			err;	// Error accumulator used in Bresenham's algorithm
	t_point2d	cur;	// Current point plotted (from a and steps toward b)
	t_point2d	b;		// Ending point of the line
	t_point2d	a;		// Starting point of the line
}	t_draw;

typedef struct s_map
{
	int			fd;
	int			rows;		// Number of rows
	int			cols;		// Number of columns
	int			high;		// Highest elevation value
	int			low;		// Lowest elevation value
	bool		use_zcolor;	// apply color based on elevation (z-axis)
	double		alpha;		// Isometric projection angle (Y rotation)
	double		beta;		// Isometric projection angle (X rotation)
	double		interval;	// Spacing between points
	double		x_offset;	// Horizontal value to center or move the map
	double		y_offset;	// Vertical value to center or move the map
	double		xrotate;	// Manual rotation angle around X-axis
	double		yrotate;	// Manual rotation angle around Y-axis
	double		zrotate;	// Manual rotation angle around Z-axis
	double		zoom;		// Zoom level applied to the entire map
	double		zscale;		// Scale factor for Z-axis
	t_point3d	**grid3d;	// 2D array of original 3D points
	t_point2d	**grid2d;	// 2D array of transformed 2D points (display)
	bool		orthogonal;	// orthogonal view
}	t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*image;
	bool		x_rotation_enabled;
	bool		y_rotation_enabled;
	bool		z_rotation_enabled;
}	t_fdf;

#endif // !FDF_STRUCTS_H
