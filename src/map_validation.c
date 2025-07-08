/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:12:18 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/08 18:35:11 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

bool retangular_check(t_fdf *fdf)
{
	char	*line;
	char	**split;
	int		current_column;

	current_column = 0;
	while((line = get_next_line(fdf->fd)))
	{
		if (!line)
			return (false);
		fdf->map_y++;
		current_column = count_tokens(line, ' ');
		split = fdf_split(line, ' ');
		if (fdf->map_x == 0)
			fdf->map_x = current_column;
		else if ((fdf->map_x != current_column))
		{
			free(line);
			ft_free_array(split);
			return (false);
		}
		free(line);
		ft_free_array(split);
	}
	return (true);
}

void	open_validate_map(char *argv, t_fdf *fdf)
{

	if (!check_extension(argv))
		ft_error("not an .fdf file");
	fdf->fd = open(argv, O_RDONLY);
	if (fdf->fd < 0)
		ft_error("Can't open file.");
	if(!(retangular_check(fdf)))
		ft_error("Invalid map");
	close(fdf->fd);
}
