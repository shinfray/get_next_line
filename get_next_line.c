/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:54:04 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/17 20:00:01by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free_all(char **cache, char **line)
{
	if (*cache != NULL)
		free(*cache);
	if (*line != NULL)
		free(*line);
	*cache = NULL;
	*line = NULL;
}

static char	*ft_save_in_cache(char **line, char *str)
{
	const size_t	len_str = ft_strlen(str);
	size_t			n;
	size_t			i;
	char			*cache;

	n = (ft_strchr(str, '\n') - str) + 1;
	i = 0;
	*line = ft_strnjoin(*line, str, n);
	if (n == len_str)
		return (NULL);
	cache = ft_calloc(len_str - n + 1, sizeof(*cache));
	if (cache == NULL)
		return (NULL);
	while (str[n] != '\0')
		cache[i++] = str[n++];
	return (cache);
}

static bool	ft_retrieve_from_cache(char **cache, char **line)
{
	char	*temp;

	if (*cache != NULL)
	{
		if (ft_strchr(*cache, '\n') != NULL)
		{
			temp = ft_save_in_cache(line, *cache);
			free(*cache);
			*cache = temp;
			return (NEWLINE_FOUND);
		}
		*line = ft_strnjoin(*cache, NULL, BUFFER_SIZE);
		*cache = NULL;
	}
	return (NEWLINE_NOT_FOUND);
}

static void	ft_parser(int fd, char **line, char **cache)
{
	ssize_t	ret;
	char	buf[BUFFER_SIZE + 1];

	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == ERROR)
			return (ft_free_all(cache, line));
		else if (ret == EOF_REACHED)
			return ;
		buf[ret] = '\0';
		if (ft_strchr(buf, '\n') != NULL)
		{
			*cache = ft_save_in_cache(line, buf);
			return ;
		}
		*line = ft_strnjoin(*line, buf, ret);
	}
}

char	*get_next_line(int fd)
{
	static char	*cache[OPEN_MAX] = {NULL};
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	line = NULL;
	if (ft_retrieve_from_cache(&cache[fd], &line) == NEWLINE_NOT_FOUND)
		ft_parser(fd, &line, &cache[fd]);
	return (line);
}
//8384280
//8380128 -fsanitize=address -g
