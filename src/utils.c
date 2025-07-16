/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:55:58 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/16 14:37:44 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Exit the program as failure.
void ft_error(char *str)
{
	ft_printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
}

void	ft_free_tab(void **tab, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->grid2d)
		ft_free_tab((void **)map->grid2d, map->rows);
	if (map->grid3d)
		ft_free_tab((void **)map->grid3d, map->rows);
	free(map);
}

void ft_error_close(char *str, int fd)
{
	ft_printf("Error: %s\n", str);
	close(fd);
	exit(EXIT_FAILURE);
}

void ft_error_map(char *str, int fd, t_map *map)
{
	ft_printf("Error: %s\n", str);
	close(fd);
	free_map(map);
	exit(EXIT_FAILURE);
}


// int	check_extension(char *filename)
// {
// 	if(ft_strnstr(filename, ".fdf", ft_strlen(filename)))
// 		return (0);
// 	else
// 		return (1);
// }
