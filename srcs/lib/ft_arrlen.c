#include "lib.h"

int		arrlen(char **arr)
{
	int ret;

	if (arr == NULL)
		return (0);
	ret = 0;
	while (arr[ret] != NULL)
		ret++;
	return (ret);
}
