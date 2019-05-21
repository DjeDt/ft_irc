/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runnin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/21 16:19:23 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	init_client_list(t_client *client, int socket)
{
	FD_ZERO(&client->master);
	FD_ZERO(&client->read);
	FD_ZERO(&client->write);
	FD_SET(socket, &client->master);
	client->fd_max = socket;
}

bool	accept_connection(t_server *server, t_client *client)
{
	socklen_t			addr_len;
	struct sockaddr_in	addr;

	addr_len = sizeof(addr);
	client->new = accept(server->socket, (struct sockaddr*)&addr, &addr_len);
	if (client->new < 0)
	{
		perror("accept");
		return (false);
	}
	else
	{
		printf("[+] new connection from socket %d\n", client->new);
		FD_SET(client->new, &client->master);	// push client fd into our master list
		if (client->new > client->fd_max)				// track max connected client
			client->fd_max = client->new;
		add_users(&server->users, client->new);
	}
	return (true);
}

bool	processing(t_server *server)
{
	int	off;

	off = 0;
	while (off <= server->client.fd_max)
	{
		if (FD_ISSET(off, &server->client.read))
		{
			if (off == server->socket)
			{
				accept_connection(server, &server->client);
			}
			else
			{
				if (receive_data(server, off) != true)
					remove_user(&server->users, off);
			}
		}
		off++;
	}
	return (true);
}

bool	running(t_server *server)
{

	init_client_list(&server->client, server->socket);
	puts("waiting for connection ...");
	while (true)
	{
		server->client.read = server->client.master;
		if (select(server->client.fd_max + 1, &server->client.read, &server->client.write, NULL, NULL) < 0)
		{
			perror("select");
			return (false);
		}
		processing(server);
	}
	return (true);
}
