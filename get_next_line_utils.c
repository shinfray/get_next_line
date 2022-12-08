#include "get_next_line.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	c2 = c;
	const char	*ptr;

	ptr = NULL;
	while (1)
	{
		if (*s == c2)
			ptr = s;
		if (*s == '\0')
			return ((char *)ptr);
		++s;
	}
}

size_t	ft_strlen(char *str)
{
	const char	*const ptr = str;

	if (str == NULL)
		return (0);
	while (*(str++) != '\0')
		;	

	return (str - ptr);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	full_size;
	char	*ptr;

	full_size = size * count;
	ptr = malloc(full_size);
	if (ptr != NULL)
	{
		while (full_size-- > 0)
			*(ptr++) = '\0';
	}
	return (ptr);
}