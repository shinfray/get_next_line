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

ssize_t	ft_parse_until_newline(int fd, char *line, char **cache, char *buf)
{
	ssize_t	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	printf("%zu\n", ret);
	if (ret < 1)
		return (0);
	buf[ret] = '\0';
	if (ft_search_newline(fd, line, cache, buf) == true)
		return (0);
	else
	{
		line = ft_strnjoin(line, buf, ret);
		ret = ft_parse_until_newline(fd, line, cache, buf);
	}
	printf("%zu\n", ret);

	return (ret);
}

char	*get_next_line(int	fd)
{
	static char	**cache;
	char		*line;
	char		buf[BUFFER_SIZE + 1];

	cache = ft_calloc(OPEN_MAX, sizeof(*cache));
	line = NULL;
	if (cache != NULL)
		ft_parse_until_newline(fd, line, cache, buf);
	printf("coucou\n");

	return (line);
}
