/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:55:04 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/17 20:07:47y shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	const char	c2 = c;

	while (*s != c2)
	{
		if (*s++ == '\0')
			return (NULL);
	}
	return ((char *)s);
}

size_t	ft_strlen(const char *str)
{
	const char *const	ptr = str;

	if (str == NULL)
		return (0);
	while (*str != '\0')
		++str;
	return (str - ptr);
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
	i = -1;
	j = 0;
	if (n < s2_len)
		s2_len = n;
	str = ft_calloc(s1_len + s2_len + 1, sizeof(*str));
	if (str == NULL)
		return (NULL);
	while (++i < s1_len)
		str[i] = s1[i];
	while (j < s2_len)
		str[i++] = s2[j++];
	if (s1 != NULL)
		free(s1);
	return (str);
}
