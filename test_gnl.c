/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:20:03 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/09 15:55:17 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static char	*ft_save_in_cache(char *string_to_backup)
{
	size_t	i;
	char	*cache;

	i = -1;
	cache = ft_calloc(ft_strlen(string_to_backup), sizeof(*cache));
	if (cache == NULL)
		return (NULL);
	while (string_to_backup[++i] != '\0')
		cache[i] = string_to_backup[i];
	return (cache);
}

static char	*ft_parser(int fd, char **cache, char  **line)
{
	ssize_t	bytes_read;
	char	*buf;
	char	*newline_pos;
	char	*new_cache;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(*buf));
	if (buf == NULL)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		newline_pos = ft_strchr(buf, '\n');
		if (newline_pos != NULL)
		{
			new_cache = ft_save_in_cache(newline_pos);
			free(*cache);
			*cache = new_cache;
			return (*line);
		}
		*line = ft_strnjoin(line, buf, bytes_read);
		if (line == NULL)
			return (ft_free(&buf));
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	ft_free(&buf);
	if (bytes_read < 0)
		return (NULL);
	return (*line);
}

static char	*ft_retrieve_from_cache(char **cache, char *newline_pos)
{
	size_t	bytes_to_copy;
	char	*str;
	char	*new_cache;

	new_cache = NULL;
	if (newline_pos == NULL)
		bytes_to_copy = BUFFER_SIZE;
	else
		bytes_to_copy = (newline_pos - *cache) + 1;
	str = ft_strnjoin(NULL, *cache, bytes_to_copy);
	if (str != NULL && newline_pos != NULL && *(newline_pos + 1) != '\0')
	{
		new_cache = ft_save_in_cache(newline_pos + 1);
		if (new_cache == NULL)
			ft_free(&str);
	}
	free(*cache);
	*cache = new_cache;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;
	char		*newline_pos;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = NULL;
	if (cache != NULL)
	{
		newline_pos = ft_strchr(cache, '\n');
		line = ft_retrieve_from_cache(&cache, newline_pos);
		if (line == NULL)
			return (NULL);
	}
	if (line == NULL || newline_pos == NULL)
		if (ft_parser(fd, &cache, &line) == NULL)
			return (ft_free(&line));
	return (line);
}
