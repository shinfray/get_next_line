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

static size_t	ft_strlen(const char *str)
{
	const char	*ptr;
	
	if (str == NULL)
		return (0);
	ptr = str;
	while (*ptr != '\0')
		++ptr;	

	return (ptr - str);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	full_size;
	size_t	i;
	char	*ptr;

	full_size = size * count;
	printf("%zu ccalloc\n", full_size);
	i = 0;
	ptr = malloc(full_size);
	if (ptr != NULL)
	{
		while (i < full_size)
			ptr[i++] = '\0';
	}
	return (ptr);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;
	char	*str;

	printf("coucou\n");
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	printf("%s   s1\n", s1);
	printf("%s   s2\n", s2);
	i = 0;
	j = 0;
	if (n < s2_len)
		s2_len = n;
	str = ft_calloc(s1_len + s2_len + 1, sizeof(*str));
	if (str == NULL)
		return (NULL);
	while (i < s1_len)
	{
		str[i] = s1[i];
		++i;
	}
	while (j < s2_len)
		str[i++] = s1[j++];
	str[i] = '\0';

	printf("%s\n ====s1====\n", s1);
	printf("%s\n ====s2====\n", s2);
	printf("%s\n ====test du join====\n", str);
	return (str);
}

