#include "server.h"

bool	send_data(int fd, char *data, int size, int flag)
{
	int tmp;
	int sent;

	sent = 0;
	while (sent < size)
	{
		tmp = send(fd, data + sent, size, flag);
		if (tmp <= 0)
		{
			if (tmp < 0)
				perror("send");
			return (false);
		}
		sent += tmp;
	}
	printf("send %d data to %d socket\n", sent, fd);
	return (true);
}
