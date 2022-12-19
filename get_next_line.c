/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:20:03 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/19 18:30:10 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free_line(char **line)
{
	if (*line != NULL)
		free(*line);
	*line = NULL;
}

static char	*ft_save_in_cache(char **line, char *str, char *newline_pos)
{
	const size_t	len_str = ft_strlen(str);
	size_t			n;
	size_t			i;
	char			*cache;

	n = (newline_pos - str) + 1;
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

static void	ft_parser(int fd, char **line, char **cache)
{
	ssize_t	ret;
	char	buf[BUFFER_SIZE + 1];
	char	*newline_pos;

	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == ERROR)
			return (ft_free_line(line));
		else if (ret == EOF_REACHED)
			return ;
		buf[ret] = '\0';
		newline_pos = ft_strchr(buf, '\n');
		if (newline_pos != NULL)
		{
			*cache = ft_save_in_cache(line, buf, newline_pos);
			return ;
		}
		*line = ft_strnjoin(*line, buf, ret);
	}
}

static bool	ft_retrieve_from_cache(char **cache, char **line)
{
	char	*newline_pos;
	char	*temp;

	if (*cache != NULL)
	{
		newline_pos = ft_strchr(*cache, '\n');
		if (newline_pos != NULL)
		{
			temp = ft_save_in_cache(line, *cache, newline_pos);
			free(*cache);
			*cache = temp;
			return (NEWLINE_FOUND);
		}
		*line = ft_strnjoin(*cache, NULL, BUFFER_SIZE);
		*cache = NULL;
	}
	return (NEWLINE_NOT_FOUND);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = NULL;
	if (ft_retrieve_from_cache(&cache, &line) == NEWLINE_NOT_FOUND)
		ft_parser(fd, &line, &cache);
	return (line);
}
//8384280
//8380128 -fsanitize=address -g
