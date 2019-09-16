#include "lib.h"

void		ft_itoa(char *str, int n)
{
	int	num;
	int	count;

	num = n;
	count = 1;
	while (n /= 10)
		count++;
	while (count-- > 0)
	{
		str[count] = (num % 10) + '0';
		num /= 10;
	}
}
