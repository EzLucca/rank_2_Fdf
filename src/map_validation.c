/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:12:18 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/07 17:49:26 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

bool retangular_check(t_fdf *fdf)
{
	char	*line;
	char	**split;
	int		current_width;
	int		expected_width;

	expected_width = -1;
	while ((line = get_next_line(fdf->fd)))
	{
		split = ft_split(line, ' ');
		if(!split)
			return (false);
		current_width = 0;
		while(split[current_width])
			current_width++;
		if (expected_width == -1)
			expected_width = current_width;
		else if (current_width != expected_width)
		{
		ft_free_array(split);
		free(line);
		return (false);
		}
		fdf->map_y++;
		ft_free_array(split);
		free(line);
	}
	if (fdf->map_y == 0)
		ft_error("Empty file.");
	ft_printf("x: %d\n", fdf->map_x);
	ft_printf("y: %d\n", fdf->map_y);
	fdf->map_x = expected_width;
	if (!(fdf->map_x % fdf->map_y == 0)) // not work for M(2x9)
		return (false);
	return (true);
}

void	open_validate_map(char *argv, t_fdf *fdf)
{

	if (!check_extension(argv))
		ft_error("not an .fdf file");
	fdf->fd = open(argv, O_RDONLY);
	if (fdf->fd == -1)
		ft_error("Can't open file.");
	if(!(retangular_check(fdf)))
		ft_error("Invalid map");
	close(fdf->fd);
}
