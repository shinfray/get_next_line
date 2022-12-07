/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:31:18 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/07 18:50:59 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str != NULL && str[i] != '\0')
		++i;
	printf("%zu\n", i);
	return (i);
/*
 *
 *    const char	*const ptr = str;
 *
 *    while (str != NULL && *str != '\0')
 *        ++str;
 *    printf("%zu\n", str - ptr);
 *    return (str - ptr);
 */
}

char	*ft_strnjoin_gnl(char *dest, char *src, size_t n)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(sizeof(*ptr) * ((ft_strlen(dest) + n + 1)));
	//printf("%zu\n", ft_strlen(dest));
	while (dest != NULL && *dest != '\0')
		ptr[i++] = *(dest++);
	while (n-- > 0)
		ptr[i++] = *(src++);
	ptr[i] = '\0';
	printf("%s\n", ptr);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX];
	char		*temp_buf;
	char		*line;
	ssize_t		ret;
	size_t		i;
	//char		*ptr;

	temp_buf = malloc(sizeof(*temp_buf) * BUFFER_SIZE);
	line = NULL;
	ret = 1;
	while (ret > 0)
	{
		i = 0;
		ret = read(fd, temp_buf, BUFFER_SIZE);
	//	printf("%zd\n", ret);
		if (ret > 0)
			buf[fd] = malloc(sizeof(*buf[fd]) * (ret + 1));
		else
		{
			free(temp_buf);
			return (line);
		}
		while (i < (size_t)ret)
		{
			buf[fd][i] = temp_buf[i];
			++i;
		}
		buf[fd][i] = '\0';
	//	printf("%s\n", buf[fd]);
		free(temp_buf);
		i = 0;
		while (i < (size_t)ret)
		{
			if (buf[fd][i] == '\n' )
			{
				ft_strnjoin_gnl(line, buf[fd], i + 1);
			//	printf("%s\n", line);
				return (line);
			}
			else
				++i;
		}
		ft_strnjoin_gnl(line, buf[fd], i);
		//printf("%s\n", line);
	}
	free(temp_buf);
	return (line);
}
