#include "lib.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char*)dst;
	s2 = (unsigned char*)src;
	i = 0;
	if (s2 < s1)
	{
		s1 += len - 1;
		s2 += len - 1;
		while (len-- > 0)
			*s1-- = *s2--;
	}
	else
	{
		while (i < len)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	return (dst);
}
