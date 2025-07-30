/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:46:45 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/30 22:37:29 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/fdf_bonus.h"

static void	process_map_line(int fd, t_map *map, char *tmp)
{
	char	*line;
	int		current_column;

	line = ft_strtrim (tmp, "\n");
	free (tmp);
	if (!line || !points_check(line))
		ft_error_map("Invalid point.", fd, map);
	map->rows++;
	current_column = count_tokens(line, ' ');
	if (map->cols == 0)
		map->cols = current_column;
	else if ((map->cols != current_column))
	{
		free (line);
		ft_error_map("Missing point.", fd, map);
	}
	free (line);
}

static void	grid_check(int fd, t_map *map)
{
	char	*tmp;

	tmp = get_next_line(fd);
	if (!tmp)
		ft_error_map("Map is empty.", fd, map);
	while (tmp)
	{
		process_map_line(fd, map, tmp);
		tmp = get_next_line(fd);
	}
}

t_map	*open_validate_map(char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		ft_error ("Can't open file.");
	map = malloc(sizeof(t_map));
	if (!map)
		ft_error_close ("Cannot malloc for map.", fd);
	init_map (map);
	grid_check (fd, map);
	close (fd);
	allocate_grid (map);
	map->interval = ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 2;
	map->interval = ft_max(2, map->interval);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error ("Can't re-open file.");
	parse_map (fd, map);
	close (fd);
	set_zcolor (map);
	return (map);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2 || !ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
		ft_error("Correct usage: ./fdf <map_name>.fdf");
	ft_bzero (&fdf, sizeof(fdf));
	init_fdf (argv[1], &fdf);
	display_menu (fdf.mlx);
	if (mlx_image_to_window (fdf.mlx, fdf.image, 0, 0) == -1)
	{
		free_map(fdf.map);
		mlx_close_window(fdf.mlx);
		ft_error("error image");
	}
	mlx_loop_hook (fdf.mlx, loop_handler, &fdf);
	mlx_scroll_hook (fdf.mlx, &ft_scroll_hook, &fdf);
	mlx_resize_hook (fdf.mlx, resize_hook, &fdf);
	mlx_loop (fdf.mlx);
	mlx_delete_image (fdf.mlx, fdf.image);
	mlx_terminate (fdf.mlx);
	free_map (fdf.map);
	return (EXIT_SUCCESS);
}
