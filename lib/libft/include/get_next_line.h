/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:01:03 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/07 15:54:49 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1 
# endif

// ------------------------ Libraries ------------------------ //

# include <unistd.h>
# include <stdlib.h>

// ------------------------ Prototypes ------------------------ //

/** 
 * Read the file descriptor and return a line.
 * @param fd: File descriptor where read the data.
 * @return Line read or NULL on error.
 */
char	*get_next_line(int fd);

/** 
 * Count the length of the string 's'.
 * @param s: String to count the length.
 * @return Length of the string 's'.
 */
size_t	ft_strlen_gnl(char *s);

/** 
 * Copies bytes from one memory area to another; the areas must not overlap.
 * @param dest: Pointer to the destination memory area.
 * @param src: Pointer to the source memory area.
 * @param n: Number of bytes to copy.
 * @return Pointer to the destination memory area.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * Search for the first ocurence of 'c' in the string.
 * @param s: String to search.
 * @param c: Character to search inside the string.
 * @return: Pointer to the location on the string or NULL if not found.
 */
char	*ft_strchr_gnl(char *s, int c);

/**
 * Concatenates two strings with dinamic allocation.
 * @param buffer: String that store the previous call.
 * @param tmp_buf: String that store the new call.
 * @return: Pointer to the string or NULL if allocation fails.
 */
char	*ft_strjoin_gnl(char *buffer, char *tmp_buf);

char	*ft_strndup_gnl(const char *s, size_t n);

#endif
