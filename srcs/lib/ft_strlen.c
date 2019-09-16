#include "lib.h"

ssize_t	ft_strlen(const char *str)
{
	int count;

	if (!str)
		return (-1);
	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}
