/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:46:45 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/16 16:05:36 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	grid_check(int fd, t_map *map)
{
	char	*line;
	char	*tmp;
	int		current_column;

	current_column = 0;
	while((tmp = get_next_line(fd)))
	{
		line = ft_strtrim(tmp, "\n");
		free(tmp);
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
		free(line);
	}
	return ;
}

void	init_map(t_map *map)
{
	map->alpha = 0.46373398 / 2; // Rotation angle
	map->beta = 0.46373398;
	map->xrotate = 0;
	map->yrotate = 0;
	map->zrotate = 0;
	map->x_offset = WIDTH / 2;  // For centering the image
	map->y_offset = HEIGHT / 2; // For centering the image
	map->zoom = 1; // Zoom factor
	map->zscale = 1; // Scale the z axis for depth or elevation
	map->use_zcolor = false;
	map->high = INT_MIN; // tracks the highest z_value
	map->low = INT_MAX; // tracks the lowest z_value
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
		ft_error("Can't open file.");
	map = malloc(sizeof(t_map));
	if (!map)
		ft_error_close("Cannot malloc for map.", fd);
	init_map(map);
	grid_check(fd, map);  // checkar free map em caso de erro
	close(fd);
	allocate_grid(map);
	// map->interval = ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 2;
	// map->interval = ft_max(2, map->interval);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Can't re-open file.");
	parse_map(fd, map);
	close(fd);
	set_zcolor(map);
	return (map);
}

void	init_fdf(char *filename, t_fdf	*fdf)
{
	fdf->map = open_validate_map(filename);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!fdf->mlx)
	{
		free_map(fdf->map);
		ft_error("Error: fdf.mlx");
	}
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image)
	{
		free_map(fdf->map);
		mlx_close_window(fdf->mlx);
		ft_error("Error: fdf.image");
	}
}

int	main(int argc, char **argv)
{

	t_fdf	fdf;

	if (argc != 2 || !ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
		ft_error("Correct usage: ./fdf <map_name>.fdf");
	ft_bzero(&fdf, sizeof(fdf));
	init_fdf(argv[1], &fdf);
	display_menu(fdf.mlx);
	draw_image(&fdf);
	if(mlx_image_to_window(fdf.mlx, fdf.image, 0, 0) == -1)
	{
		free_map(fdf.map);
		mlx_close_window(fdf.mlx);
		ft_error("error image");
	}
	mlx_loop_hook(fdf.mlx, loop_handler, &fdf);
	mlx_scroll_hook(fdf.mlx, &ft_scroll_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free_map(fdf.map);
	return (EXIT_SUCCESS);
}
