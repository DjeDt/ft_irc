#include "lib.h"

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\n')
		return (0);
	return (1);
}
