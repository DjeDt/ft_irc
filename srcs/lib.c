#include "server.h"

ssize_t	_strlen(const char *str)
{
	ssize_t count;

	count = 0;
	if (str == NULL)
		return (-1);
	while (str[count] != '\0')
		count++;
	return (count);
}

void	*_memset(void *data, char c, size_t size)
{
	size_t	count;
	uint8_t	*str;

	if (data == NULL)
		return (NULL);
	count = 0;
	str = (uint8_t*)data;
	while (count < size)
		str[count++] = c;
	return (data);
}

void	*_memcpy(void *dst, void *src, size_t n)
{
	uint8_t	*s1;
	uint8_t	*s2;
	size_t	i;

	i = 0;
	s1 = (uint8_t*)dst;
	s2 = (uint8_t*)src;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (s1);
}

char	*_strchr(const char *str, char c)
{
	char *ret;

	if (str != NULL)
	{
		ret = (char*)str;
		while (*ret)
		{
			if (*ret == c)
				return (ret);
			ret++;
		}
	}
	return (NULL);
}
