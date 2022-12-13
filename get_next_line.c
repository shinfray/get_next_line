#include "get_next_line.h"

void	ft_save_in_cache(int fd, char *line, char **cache, char *buf, size_t n)
{
	size_t	i;

	i = 0;
	line = ft_strnjoin(line, buf, n);
	cache[fd] = ft_calloc(ft_strlen(buf) - n + 1, sizeof(*cache[fd]));
	while (buf[n] != '\0')
		cache[fd][i++] = buf[n++];
	printf("%s\n", line);
}

bool	ft_search_newline(int fd, char *line, char **cache, char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			ft_save_in_cache(fd, line, cache, buf, i + 1);

			return (true);
		}
		else
			++i;
	}

	return (false);
}

char	ft_parse_until_newline(int fd, char *line, char **cache, char *buf)
{
	ssize_t	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret < 1)
		return (EOF_REACHED);
	buf[ret] = '\0';
	if (cache[fd] != NULL)
		line = ft_strnjoin(cache[fd], buf, BUFFER_SIZE);
	if (ft_search_newline(fd, line, cache, buf) == true)
		return (NEWLINE_FOUND);
	else
	{
		line = ft_strnjoin(line, buf, ret);
		return (NEWLINE_NOT_FOUND);
	}
}

char	*get_next_line(int	fd)
{
	static char	*cache[OPEN_MAX];
	char		*line;
	char		buf[BUFFER_SIZE + 1];
	char		file_state;

	line = NULL;
	file_state = NEWLINE_NOT_FOUND;
	while (file_state != EOF_REACHED)
	{
		file_state = ft_parse_until_newline(fd, line, cache, buf);
	}
	if (file_state == NEWLINE_FOUND)


	return (line);
}
