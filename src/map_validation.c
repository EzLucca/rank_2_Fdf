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
	char *new_line;
	char **split;
	int		i;

	i = 0;
	while ((new_line = get_next_line(fdf->fd)))
	{
		fdf->map_y++;
		split = ft_split(new_line, ' ');
		while(split[i])
		{
			fdf->map_x++;
			free(split[i]);
			i++;
		}
		free(split);
		free(new_line);
	}
	if (fdf->map_y == 0)
		ft_error("Empty file.");
	if (!(fdf->map_x % fdf->map_y == 0))
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
