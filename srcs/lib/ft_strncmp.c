#include "lib.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
		return (0);
	else
		return (*s1 - *s2);
}
