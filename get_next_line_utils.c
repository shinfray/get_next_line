#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	const char	c2 = c;

	while (*s != c2)
	{
		if (*s == '\0')
			return (NULL);
		++s;
	}
	return ((char *)s);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = ft_calloc(s1_len + s2_len + 1, sizeof(*str));
	if (str == NULL)
		return (NULL);
	while (s1_len-- > 0)
		*(str++) = *(s1++);
	while (s2_len-- > 0)
		*(str++) = *(s2++);
	*str = '\0';
	return (str);
}