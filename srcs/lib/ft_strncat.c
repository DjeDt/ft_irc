#include "lib.h"

char	*ft_strncat(char *s1, char *s2, int n)
{
	char	*ret;
	char	*str;

	ret = s1;
	str = s2;
	while (*ret != '\0')
		ret++;
	while ((*str != '\0') && n)
	{
		*ret++ = *str++;
		n--;
	}
	*ret = '\0';
	return (s1);
}
