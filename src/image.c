/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:11:41 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/16 14:29:00 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	radiant(int begin, int end, double percent)
{
	return((int)((1 - percent) * begin + percent * end));
}

double	colormix(int begin, int end, int current)
{
	double	place;
	double	dist;

	place = current - begin;
	dist = end - begin;
	if (dist == 0)
		return (1.0);
	return (place / dist);
}

int	get_color(t_point2d current, t_point2d a, t_point2d b)
{
	int	red;
	int	green;
	int	blue;
	int	percent;

	if(a.rgba == b.rgba)
		return (a.rgba);
	if (abs(b.x - a.x) > abs(b.y - a.y))
		percent = colormix(a.x, b.x, current.x);
	else
		percent = colormix(a.y, b.y, current.y);
	red = radiant((a.rgba >> 24) & 0xFF, (b.rgba >> 24) & 0xFF, percent);
	green = radiant((a.rgba >> 16) & 0xFF, (b.rgba >> 16) & 0xFF, percent);
	blue = radiant((a.rgba >> 8) & 0xFF, (b.rgba >> 8) & 0xFF, percent);
	return ((red << 24) | (green << 16) | blue << 8 | 0xFF);
}

int	colors(double percent)
{
	if (percent < 0.1)
		return (COLOR_ONE);
	else if (percent < 0.2)
		return (COLOR_TWO);
	else if (percent < 0.3)
		return (COLOR_THREE);
	else if (percent < 0.4)
		return (COLOR_FOUR);
	else if (percent < 0.5)
		return (COLOR_FIVE);
	else if (percent < 0.6)
		return (COLOR_SIX);
	else if (percent < 0.7)
		return (COLOR_SEVEN);
	else if (percent < 0.8)
		return (COLOR_EIGHT);
	else if (percent < 0.9)
		return (COLOR_NINE);
	else
		return (COLOR_TEN); 
}

void	set_zcolor(t_map *map)
{
	int		i;
	int		j;
	double	percent;
	
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			percent = colormix(map->low, map->high, map->grid3d[i][j].z);
			map->grid3d[i][j].zcolor = colors(percent);
		}
	}
}
