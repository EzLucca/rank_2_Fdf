/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:46:45 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/15 22:45:00 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// TODO:
void	grid_check(int fd, t_map *map)
{
	char	*line;
	int		current_column;

	current_column = 0;
	while((line = get_next_line(fd)))
	{
		if (!line)
			ft_error_close("Invalid map.", fd); // review free stuffs
		if (!points_check(line))
			ft_error_close("Invalid point.", fd);
		map->rows++;
		current_column = count_tokens(line, ' ');
		if (map->cols== 0)
			map->cols= current_column;
		else if ((map->cols!= current_column))
		{
			free(line);
			ft_error_close("Couldn't read file", fd);
		}
		process_line(fd, map, line);
		// ft_printf("Map cols = %d (line = \"%s\")\n", current_column, line); // DEBUG
		free(line);
	}
	return ;
}

void	init_map(t_map *map)
{
	map->alpha = 0.46373398 / 2;
	map->beta = 0.46373398;
	map->xrotate = 0;
	map->yrotate = 0;
	map->zrotate = 0;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->zoom = 1;
	map->zscale = 1;
	map->use_zcolor = false;
	map->high = INT_MIN;
	map->low = INT_MAX;
	map->rows = 0;
	map->cols = 0;
	map->grid2d = NULL;
	map->grid3d = NULL;
}

t_map	*open_validate_map(char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error_close("Can't open file.", fd);
	map = malloc(sizeof(t_map));
	if (!map)
		ft_error_close("", fd);
	init_map(map);
	grid_check(fd, map);
	close(fd);

	return (map);
}

t_fdf	*init_fdf(char *filename)
{
	static	t_fdf	fdf;

	fdf.map = open_validate_map(filename);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!fdf.mlx)
	{
		free_map(fdf.map);
		ft_error(mlx_strerror(mlx_errno));
	}
	fdf.image = mlx_new_image(fdf.mlx, WITH, HEIGHT);
	if (!fdf.image)
	{
		free_map(fdf.map);
		mlx_close_window(fdf.mlx);
		ft_error(mlx_strerror(mlx_errno));
	}
	return (&fdf);
}

int	main(int argc, char **argv)
{

	t_fdf	*fdf;

	if (argc != 2 || !check_extension(argv[1]))
		ft_error("Correct usage: ./fdf <map_name>.fdf");
	fdf = init_fdf(argv[1]);

	ft_bzero(&fdf, sizeof(fdf));
	open_validate_map(argv[1], &fdf);
	parse_map(argv[1], &fdf);
	init_camera(&fdf.camera, &fdf);
	loop_mlx(&fdf);
	return (EXIT_SUCCESS);
}
