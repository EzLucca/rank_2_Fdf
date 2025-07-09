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

void	draw(t_fdf *fdf)
{
	int	x, y;

	clear_image(&fdf->image);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
				draw_line(fdf, fdf->map.points[y][x], fdf->map.points[y][x + 1]);
			if (y < fdf->map.height - 1)
				draw_line(fdf, fdf->map.points[y][x], fdf->map.points[y + 1][x]);
			x++;
		}
		y++;
	}
}


