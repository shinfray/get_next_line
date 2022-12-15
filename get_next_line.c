/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:54:04 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/15 16:32:42 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free_cache(char **cache, char **line)
{
	if (*cache != NULL)
		free(*cache);
	if (*line != NULL)
		free(*line);
	*cache = NULL;
	*line = NULL;
}

static void	ft_save_in_cache(char **line, char *buf, char *cache)
{
	const size_t	len_buf = ft_strlen(buf);
	size_t			n;
	size_t			i;

	n = (ft_strchr(buf, '\n') - buf) + 1;
	i = 0;
	*line = ft_strnjoin(*line, buf, n);
	if (n == len_buf)
		return ;
	cache = ft_calloc(len_buf - n + 1, sizeof(*cache));
	if (cache == NULL)
		return ;
	while (buf[n] != '\0')
		cache[i++] = buf[n++];
}

static bool	ft_retrieve_from_cache(char **cache, char **line, char *buf)
{
	size_t	i;

	if (*cache != NULL)
	{
		i = -1;
		while (*cache[++i] != '\0')
			buf[i] = *cache[i];
		buf[i] = '\0';
		free(*cache);
		*cache = NULL;
		if (ft_strchr(buf, '\n') != NULL)
		{
			ft_save_in_cache(line, buf, *cache);
			return (NEWLINE_FOUND);
		}
		*line = ft_strnjoin(*line, buf, BUFFER_SIZE);
	}
	return (NEWLINE_NOT_FOUND);
}

static void	ft_parser(int fd, char **line, char *buf, char **cache)
{
	ssize_t	ret;
	
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == ERROR)
			return (ft_free_cache(cache, line));
		else if (ret == EOF_REACHED)
			return ;
		buf[ret] = '\0';
		if (ft_strchr(buf, '\n') != NULL)
			return (ft_save_in_cache(line, buf, *cache));
		else
			*line = ft_strnjoin(*line, buf, ret);
	}
}

char	*get_next_line(int fd)
{
	static char	cache[OPEN_MAX] = {NULL};
	char		*line;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE > SSIZE_MAX)
		return (NULL);
	line = NULL;
	if (ft_retrieve_from_cache(&cache[fd], &line, buf) != NEWLINE_FOUND)
		ft_parser(fd, &line, buf, &cache[fd]);
	return (line);
}
