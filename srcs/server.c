#include "server.h"

static bool	is_valid_argument(const char *str)
{
	int count;

	count = 0;
	while (str[count] != '\0')
	{
		if (str[count] < '0' | str[count] > '9')
			return (false);
		count++;
	}
	return (true);
}

int main(int ac, char **av)
{
	t_server server;

	if (ac != 2)
	{
		error(MISSING_ARG, av[0]);
		return (ERR);
	}
	if (is_valid_argument(av[1]) != true)
	{
		error(INVALID_PORT, av[1]);
		return (ERR);
	}
	if (initialize(&server, av[1]) != true)
		return (ERR);
	if (running(&server) != true)
		return (ERR);
	return (SCS);
}
