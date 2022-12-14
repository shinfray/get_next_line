/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:54:04 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/14 13:40:36 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_all(char **cache, char **line)
{
	if (*cache != NULL)
		free(*cache);
	if (*line != NULL)
		free(*line);
	*cache = NULL;
	*line = NULL;
}

void	ft_retrieve_from_cache(char **cache, char **line)
{
	if (*cache != NULL)
	{
		*line = ft_strnjoin(*cache, NULL, BUFFER_SIZE);
		*cache = NULL;
	}
}

void	ft_save_in_cache(char **line, char *buf, char **cache, int fd)
{
	size_t	n;
	size_t	i;

	n = (ft_strchr(buf, '\n') - buf) + 1;
	i = 0;
	*line = ft_strnjoin(*line, buf, n);
	cache[fd] = ft_calloc(ft_strlen(buf) - n + 1, sizeof(*cache[fd]));
	while (buf[n] != '\0')
		cache[fd][i++] = buf[n++];
}

char	ft_parse(int fd, char **line, char *buf)
{
	ssize_t	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == 0)
		return (EOF_REACHED);
	if (ret == -1)
		return (ERROR);
	buf[ret] = '\0';
	if (ft_strchr(buf, '\n') != NULL)
		return (NEWLINE_FOUND);
	else
	{
		*line = ft_strnjoin(*line, buf, ret);
		return (NEWLINE_NOT_FOUND);
	}
}

char	*get_next_line(int fd)
{
	static char	*cache[OPEN_MAX];
	char		*line;
	char		buf[BUFFER_SIZE + 1];
	char		file_state;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE > SSIZE_MAX)
		return (NULL);
	file_state = NEWLINE_NOT_FOUND;
	line = NULL;
	ft_retrieve_from_cache(&cache[fd], &line);
	while (file_state != EOF_REACHED)
	{
		file_state = ft_parse(fd, &line, buf);
		if (file_state == NEWLINE_FOUND)
		{
			ft_save_in_cache(&line, buf, cache, fd);
			return (line);
		}
		else if (file_state == ERROR)
		{
			ft_free_all(&cache[fd], &line);
			return (NULL);
		}
	}
	return (line);
}
