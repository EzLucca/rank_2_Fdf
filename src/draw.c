/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:11:00 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 17:13:16 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// void	draw_line(t_point a, t_point b, mlx_image_t *img)
// {
// }
//
// void draw_map_lines(t_map *map)
// {
// }
//
//
// void	project_all_points(t_map *map)
// {
// }
// t_point project_point(t_point p, t_map *map)
// {
// 	float angle = ISO_ANGLE;
// 	int zoom = map->zoom;
// 	float elev_scale = map->elev_scale;
//
// 	t_point projected;
//
// 	p.x *= zoom;
// 	p.y *= zoom;
// 	p.z *= elev_scale;
// 	// ft_printf("ORIGINAL: x=%d y=%d z=%d\n", p.x, p.y, p.z);
//
// 	projected.x = (p.x - p.y) * cos(angle) + map->camera.x_offset;
// 	projected.y = (p.x + p.y) * sin(angle) - p.z + map->camera.y_offset;
// 	projected.color = p.color;
// 	// ft_printf("Projected: (%d, %d)\n", (int)projected.x, (int)projected.y);
// 	return projected;
// }
