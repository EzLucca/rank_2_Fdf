/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:00:41 by edlucca           #+#    #+#             */
/*   Updated: 2025/06/30 17:37:56 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	p;

	if (!s)
		return (0);
	p = 0;
	while (s[p])
		p++;
	return (p);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	c = (unsigned char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *) &s[i]);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char			*tmp_dst;
	const unsigned char		*tmp_src;

	if (!dest || !src)
		return (NULL);
	tmp_dst = (unsigned char *) dest;
	tmp_src = (const unsigned char *) src;
	while (n--)
		*(tmp_dst++) = *(tmp_src++);
	return (dest);
}

char	*ft_strndup_gnl(const char *s, size_t n)
{
	char	*dst;
	size_t	i;

	if (!s)
		return (NULL);
	dst = malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dst[i] = s[i];
		i++;
	}
	dst[n] = '\0';
	return (dst);
}

char	*ft_strjoin_gnl(char *buffer, char *tmp_buf)
{
	int		s1_len;
	int		s2_len;
	char	*string;

	s1_len = ft_strlen_gnl(buffer);
	s2_len = ft_strlen_gnl(tmp_buf);
	if (!tmp_buf)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	s1_len = ft_strlen_gnl(buffer);
	s2_len = ft_strlen_gnl(tmp_buf);
	string = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!string)
		return (free(buffer), NULL);
	ft_memcpy(string, buffer, s1_len);
	ft_memcpy(string + s1_len, tmp_buf, s2_len);
	string[s1_len + s2_len] = '\0';
	free(buffer);
	return (string);
}
