/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:46:45 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/07 14:57:08 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


// void parse_map(int file, int x, int y)
// {
// 	t_parse	m;
// 	char	*str;
//
// 	ft_bzero(&m, sizeof(t_parse));
// 	m.file = file;
// 	str = get_next_line(file);
// 	while(*str)
// 	{
// 		// split
// 		// count elementes in string
// 		//
// 	}
//
// 	// get next line to read first line
// 	//
// 	// needs to get the x value to compare with the others
// 	// or count the number of ints and divide until remainder is zero
// 	//
// 	// split
//
// }

int	main(int argc, char **argv)
{

	t_fdf	fdf;

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
