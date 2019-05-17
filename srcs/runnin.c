#include "server.h"

void	init_client_list(t_server *server, t_client *client)
{
	FD_ZERO(&client->master);
	FD_ZERO(&client->backup);
	FD_SET(server->socket, &client->master);
	client->fd_max = server->socket;
}

bool	accept_connection(t_server *server, t_client *client, t_single *single)
{
	single->len = sizeof(single->addr);
	single->new = accept(server->socket, (struct sockaddr*)&single->addr, &single->len);
	if (single->new < 0)
	{
		perror("accept");
		return (false);
	}
	else
	{
		FD_SET(single->new, &client->master);	// push client fd into our master list
		if (single->new > client->fd_max)		// track max connected client
			client->fd_max = single->new;
		printf("[+] new connection from socket %d\n", single->new);
	}
	return (true);
}

bool	running(t_server *server)
{
	int			count;
	t_client	client;
	t_users		*users;

	users = NULL;
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
					if (accept_connection(server, &client, &client.single) == true)
						add_users(&users, client.single);
				}
				else
				{
					if (receive_data(server, &client, count) != true)
						remove_user(&users, count);
					/* else */
					/* 	interpreter(); */
				}
			}
			count++;
		}
	}
	return (true);
}
