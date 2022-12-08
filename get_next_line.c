#include "get_next_line.h"

void	ft_save_in_cache(int fd, char *line, char **cache, char *buf, size_t n)
{
	line = ft_strnjoin(line, buf, n);
	while (buf[n] != '\0')
	{
		*cache[fd] = buf[n];
		++(cache[fd]);
		++n;
	}
}

bool	ft_search_newline(int fd, char *line, char **cache, char *buf)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
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

ssize_t	ft_parse_until_newline(int fd, char *line, char **cache)
{
	ssize_t	ret;
	char	buf[BUFFER_SIZE + 1];

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret < 1)
		return (0);
	buf[BUFFER_SIZE] = '\0';
	printf("%s ===buffer====\n", buf);
	if (ft_search_newline(fd, line, cache, buf) == true)
	{
		return (0);
	}
	else
	{
		printf("it's in search nl\n");
		line = ft_strnjoin(line, buf, BUFFER_SIZE);
		printf("%s ========= line\n", line);
		ret = ft_parse_until_newline(fd, line, cache);
	}

	return (ret);
}

char	*get_next_line(int	fd)
{
	static char	**cache;
	char		*line;

	cache = ft_calloc(OPEN_MAX, sizeof(*cache));
	line = NULL;
	if (cache == NULL)
		return (NULL);
	ft_parse_until_newline(fd, line, cache);

	return (line);
}
