/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:55:04 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/13 16:13:51 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	const char	c2 = c;

	while (*s != c2)
	{
		if (*s == '\0')
			return (NULL);
		++s;
	}
	return ((char *)s);
}

size_t	ft_strlen(const char *str)
{
	const char	*ptr;

	if (str == NULL)
		return (0);
	ptr = str;
	while (*ptr != '\0')
		++ptr;
	return (ptr - str);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	full_size;
	size_t	i;
	char	*ptr;

	full_size = size * count;
	i = 0;
	ptr = malloc(full_size);
	if (ptr != NULL)
	{
		while (i < full_size)
			ptr[i++] = '\0';
	}
	return (ptr);
}

char	*ft_strnjoin(char *s1, char const *s2, size_t n)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	j = 0;
	if (n < s2_len)
		s2_len = n;
	str = ft_calloc(s1_len + s2_len + 1, sizeof(*str));
	if (str == NULL)
		return (NULL);
	while (i < s1_len)
	{
		str[i] = s1[i];
		++i;
	}
	while (j < s2_len)
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
