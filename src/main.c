/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:46:45 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/04 15:29:04 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Exit the program as failure.
static void ft_error(char *str)
{
	ft_printf("Error: %s", str);
	exit(EXIT_FAILURE);
}

void parse_map(int file, int x, int y)
{
	t_parse	m;

	ft_bzero(&m, sizeof(t_parse));
	m.file = file;

}

int	main(int argc, char **argv)
{

	t_fdf	fdf;
	int		file;

	ft_bzero(&fdf, sizeof(fdf));
	if (argc != 2)
		ft_error("Correct usage: ./fdf <map>\n");
	// read map
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		ft_error("Can't open file.\n");
	// Parsing call
	fdf.points = parse_map(file, fdf.points->map_x, fdf.points->map_z);
	close(file);
	// draw lines

	// mlx loop
	loop_mlx(&fdf);
	return (EXIT_SUCCESS);
}
