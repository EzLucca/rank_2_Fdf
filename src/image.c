/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:11:41 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 17:14:24 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// void	put_pixel(t_map map, int x, int y, int color)
// {
// 	char	*dst;
//
// 	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
// 		return;
// 	dst = map.img->pixels + (y * map.img->height + x * (map.img->count / 8));
// 	*(unsigned int *)dst = color;
// }

void	clear_image(mlx_image_t *img)
{
	ft_bzero(img->pixels, img->width * img->height * 4);
}
