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
