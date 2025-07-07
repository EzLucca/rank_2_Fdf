/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:55:58 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/07 14:56:30 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Exit the program as failure.
void ft_error(char *str)
{
	ft_printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
}

bool	check_extension(char *filename)
{
	if(ft_strnstr(filename, ".fdf", ft_strlen(filename)))
		return (true);
	return (false);
}
