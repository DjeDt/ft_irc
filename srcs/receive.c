#include "server.h"

int		receive_full(int count, char *data, size_t size, int flag)
{
	int	tmp;
	int	read;
	int data_len;

	tmp = 0;
	read = 0;
	data_len = 0;
	while (size > 0)
	{
		tmp = recv(count, data + read, size, flag);
		if (tmp < 1)
		{
			printf("[-] Can't read from %d socket. Closing it\n", count);
			return (-1);
		}
		read += tmp;
		size -= tmp;
		if (_strchr(data, '\n') != NULL)
			return (MAX_INPUT_LEN - size);
	}
	return (1);
}

bool	receive_data(t_server *server, t_client *client, int count)
{
	int		curr;
	int		data_len;
	char	data[MAX_INPUT_LEN] = {0};

	data_len = receive_full(count, data, MAX_INPUT_LEN, 0);
	if (data_len > 0)
	{
		curr = 0;
		printf("received %d data from socket %d\n", data_len, count);
		while (curr <= client->fd_max)
		{
			if (FD_ISSET(curr, &client->master))
			{
				if (curr != server->socket && curr != count)
				{
					send_data(curr, data, data_len, 0);
					// if == false -> do something
				}
			}
			curr++;
		}
		return (true);
	}
	close(count);
	FD_CLR(count, &client->master);
	return (false);
}
