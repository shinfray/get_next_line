/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:20:03 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/09 13:25:51 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free_all(char **line, char **buf)
{
	if (line != NULL && *line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	if (buf != NULL && *buf != NULL)
	{
		free(*buf);
		*buf = NULL;
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
	while (*string_to_backup[++i] != '\0')
		cache[i] = string_to_backup[i];
	return (cache);
}

static char	*ft_parser(int fd, char **line)
{
	ssize_t	bytes_read;
	char	*buf;
	char	*newline_pos;

	bytes_read = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(*buf));
	if (buf == NULL)
		return (ft_free_all(line, NULL));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == ERROR)
			return (ft_free_all(line, &buf));
		else if (bytes_read == EOF_REACHED)
			return (ft_free_all(NULL, &buf));
		buf[bytes_read] = '\0';
		newline_pos = ft_strchr(buf, '\n');
		if (newline_pos != NULL)
			return (ft_save_in_cache(line, &buf, newline_pos));
		*line = ft_strnjoin(line, buf, bytes_read);
		if (*line == NULL)
			return (ft_free_all(NULL, &buf));
	}
	return (NULL);
}

static char	ft_retrieve_from_cache(char **cache)
{
	size_t	bytes_to_copy;
	char	*newline_pos;
	char	*str;
	char	*new_cache;

	newline_pos = ft_strchr(*cache, '\n');
	if (newline_pos == NULL)
		bytes_to_copy = BUFFER_SIZE;
	else
		bytes_to_copy = (newline_pos - *cache) + 1;
	str = ft_strnjoin(NULL, cache, bytes_to_copy);
	if (str != NULL && newline_pos != NULL && (newline_pos + 1) != '\0')
	{
		new_cache = ft_save_in_cache(newline_pos + 1);
		if (new_cache == NULL)
		{
			free(str);
			str = NULL;
		}
	}
	free(*cache);
	*cache = new_cache;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = NULL;
	if (cache != NULL)
	{
		line = ft_retrieve_from_cache(&cache);
		if (line == NULL)
			return (ft_free_all(NULL, &cache));
	}
	if (line == NULL || cache == NULL)
		parser


	if (ft_retrieve_from_cache(&cache, &line) == NEWLINE_NOT_FOUND)
		cache = ft_parser(fd, &line);
	return (line);
}
