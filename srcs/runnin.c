#include "server.h"

/* bool	accept_connection() */
/* { */

/* } */

void	init_client_list(t_server *server, t_client *client)
{
	FD_ZERO(&client->master);
	FD_ZERO(&client->backup);

	FD_SET(server->socket, &client->master);
	client->fd_max = server->socket;
}


// DEBUG
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

bool	accept_connection(t_server *server, t_client *client)
{
	int					new;
	socklen_t			len_client;
	struct sockaddr_in	addr_client;

	len_client = sizeof(addr_client);
	new = accept(server->socket, (struct sockaddr*)&addr_client, &len_client);
	if (new < 0)
	{
		perror("accept");
		return (false);
	}
	else
	{
		FD_SET(new, &client->master);	// push client fd into our master list
		if (new > client->fd_max)		// track max connected client
			client->fd_max = new;
		printf("[+] new connection from socket %d\n", new);
	}
	return (true);
}

bool	receive_data(t_server *server, t_client *client, int count)
{
	int		curr;
	int		data_len;
	char	data[256] = {0};

	data_len = recv(count, data, 256, 0);
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
					if (send(curr, data, data_len, 0) < 0)
						perror("send");
				}
			}
			curr++;
		}
		return (true);
	}
	else if (data_len < 0)
		perror("recv");
	else if (data_len == 0)
		printf("connection closed from %d socket\n", count);
	close(count);
	FD_CLR(count, &client->master);
	return (false);
}

bool	running(t_server *server)
{
	int			count;
	t_client	client;

	init_client_list(server, &client);
	printf("waiting for connection ...\n");
	while (true)
	{
		client.backup = client.master;
        if (select(client.fd_max + 1, &client.backup, NULL, NULL, NULL) < 0)
		{
            perror("select");
			return (false);
		}
		count = 0;
		while (count <= client.fd_max)
		{
			if (FD_ISSET(count, &client.backup))
			{
				if (count == server->socket)
				{
					accept_connection(server, &client);
				}
				else
				{
					receive_data(server, &client, count);
				}
			}
			count++;
		}
	}
	return (true);
}
