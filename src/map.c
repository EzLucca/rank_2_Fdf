/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:37:46 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 17:12:03 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	open_validate_map(char *argv, t_fdf *fdf)
{
	if (!check_extension(argv))
		ft_error("not an .fdf file");
	fdf->fd = open(argv, O_RDONLY);
	if (fdf->fd < 0)
		ft_error_close("Can't open file.", fdf); //close fd
	if(!(retangular_check(fdf)))
		ft_error_close("Invalid map", fdf); //close fd
	

	close(fdf->fd);
}

// int		create_argb(int a, int r, int g, int b)
// {
// 	return (a << 24 | r << 16 | g << 8 | b);
// }
//
// for (int i =0 ; i< 200  ; i++)
// {
// 		for(int k = 0; k<200; k++){
// 			char *dst2;
// 			// 8 = sizeof(char)
// 			dst2 = ptr2 + (k * size_line1 + i * bit_per_pixel1 / 8 );
// 			*(unsigned int*)dst2 = create_argb(0,0,255,0);
// 		}
// }
//
//void	init_file(t_var *var, char *path)
// {
// 	int		fd;
// 	int		i;
//
// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		ft_error("file open error");
// 	get_map_size(var, fd);
// 	close(fd);
// 	if (var->map_height <= 0 || var->map_width <= 0)
// 		ft_error("file values error: no values");
// 	i = 0;
// 	var->map = (int **)malloc(sizeof(int *) * var->map_height);
// 	if (!(var->map))
// 		ft_error("map malloc error");
// 	while (i < var->map_height)
// 	{
// 		var->map[i] = malloc(sizeof(int) * var->map_width);
// 		if (!(var->map[i++]))
// 			ft_error("map malloc error");
// 	}
// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		ft_error("file open error");
// 	save_map_data(var, fd);
// 	close(fd);
// }
