/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:46:45 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 16:53:14 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char **argv)
{

	t_map	fdf;

	if (argc != 2)
		ft_error("Correct usage: ./fdf <map>");
	ft_bzero(&fdf, sizeof(fdf));
	open_validate_map(argv[1], &fdf);
	// Parsing 
	// fdf.points = parse_map(file, fdf.points->map_x, fdf.points->map_z);
	// draw lines
	loop_mlx(&fdf);
	return (EXIT_SUCCESS);
}
