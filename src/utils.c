/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:55:58 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/09 17:18:49 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Exit the program as failure.
void ft_error(char *str)
{
	ft_printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
}

void ft_error_close(char *str, t_map *map)
{
	ft_printf("Error: %s\n", str);
	close(map->fd);
	exit(EXIT_FAILURE);
}

void remove_newline(char *line)
{
	int i = 0;

	if (!line)
		return;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return;
		}
		i++;
	}
}

void	check_extension(char *filename)
{
	if(ft_strnstr(filename, ".fdf", ft_strlen(filename)))
		return ;
	ft_error("not an .fdf file");
}
