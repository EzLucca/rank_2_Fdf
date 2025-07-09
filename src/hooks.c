/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:11:16 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 17:13:04 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// int	handle_key(int key, t_fdf *fdf)
// {
// 	if (key == 53) // ESC
// 		exit(0);
// 	else if (key == 126) // Up arrow
// 		fdf->camera.y_offset -= 10;
// 	else if (key == 125) // Down arrow
// 		fdf->camera.y_offset += 10;
// 	// Add more controls: zoom, projection, rotation...
// 	draw(fdf);
// 	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->image.img_ptr, 0, 0);
// 	return (0);
// }
//
// void	setup_hooks(t_fdf *fdf)
// {
// 	mlx_key_hook(fdf->win_ptr, handle_key, fdf);
// }
