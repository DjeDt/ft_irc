#include "lib.h"

void	ft_flush(int socket)
{
	char trash[512];

	while (true)
	{
		if (recv(socket, trash, 512, 0) < 1)
			break ;
	}
}
