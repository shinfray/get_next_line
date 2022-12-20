/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:22:59 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/20 15:06:05 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_free_all(char **line, char **buf)
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
}

static char	*ft_save_in_cache(char **line, char **str, char *newline_pos)
{
	const size_t	len_str = ft_strlen(*str);
	size_t			n;
	size_t			i;
	char			*cache;

	n = (newline_pos - *str) + 1;
	i = 0;
	*line = ft_strnjoin(line, *str, n);
	if (n == len_str)
		cache = NULL;
	else
		cache = ft_calloc(len_str - n + 1, sizeof(*cache));
	if (cache != NULL)
	{
		while ((*str)[n] != '\0')
			cache[i++] = (*str)[n++];
	}
	ft_free_all(NULL, str);
	return (cache);
}

static void	ft_parser(int fd, char **line, char **cache)
{
	ssize_t	ret;
	char	*buf;
	char	*newline_pos;

	ret = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(*buf));
	if (buf == NULL)
		return (ft_free_all(line, &buf));
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == ERROR)
			return (ft_free_all(line, &buf));
		else if (ret == EOF_REACHED)
			return (ft_free_all(NULL, &buf));
		buf[ret] = '\0';
		newline_pos = ft_strchr(buf, '\n');
		if (newline_pos != NULL)
		{
			*cache = ft_save_in_cache(line, &buf, newline_pos);
			return (ft_free_all(NULL, &buf));
		}
		*line = ft_strnjoin(line, buf, ret);
	}
}

static bool	ft_retrieve_from_cache(char **cache, char **line)
{
	char	*newline_pos;

	if (*cache != NULL)
	{
		newline_pos = ft_strchr(*cache, '\n');
		if (newline_pos != NULL)
		{
			*cache = ft_save_in_cache(line, cache, newline_pos);
			return (NEWLINE_FOUND);
		}
		*line = ft_strnjoin(cache, NULL, BUFFER_SIZE);
	}
	return (NEWLINE_NOT_FOUND);
}

char	*get_next_line(int fd)
{
	static char	*cache[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = NULL;
	if (ft_retrieve_from_cache(&cache[fd], &line) == NEWLINE_NOT_FOUND)
		ft_parser(fd, &line, &cache[fd]);
	return (line);
}
