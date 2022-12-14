/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:54:04 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/14 16:04:02y shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_cache(char **cache, char **line)
{
	if (*cache != NULL)
		free(*cache);
	if (*line != NULL)
		free(*line);
	*cache = NULL;
	*line = NULL;
}

void	ft_save_in_cache(char **line, char *buf, char *cache)
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
//	printf("\n===%s===\n", cache);
}

char	ft_retrieve_from_cache(char **cache, char **line, char *buf)
{
	size_t	i;

	if (*cache != NULL)
	{
		i = 0;
		while (*cache[i] != '\0')
		{
			buf[i] = *cache[i];
			++i;
		}
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
	static char	*cache[OPEN_MAX] = {NULL};
	char		*line;
	char		buf[BUFFER_SIZE + 1];
	char		file_state;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE > SSIZE_MAX)
		return (NULL);
	line = NULL;
	if (ft_retrieve_from_cache(&cache[fd], &line, buf) == NEWLINE_FOUND)
		return (line);
	file_state = NEWLINE_NOT_FOUND;
	while (file_state != EOF_REACHED)
	{
		file_state = ft_parse(fd, &line, buf);
		if (file_state == NEWLINE_FOUND)
		{
			ft_save_in_cache(&line, buf, cache[fd]);
			return (line);
		}
		else if (file_state == ERROR)
		{
			ft_free_cache(&cache[fd], &line);
			return (NULL);
		}
	}
	return (line);
}
