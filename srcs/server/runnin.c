/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runnin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/31 09:05:09 by ddinaut          ###   ########.fr       */
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

bool	accept_connection(t_server *server)
{
	socklen_t	len;
	t_list_user *user;

	if (!(user = create_new_user(0)))
		return (false);

	len = sizeof(user->addr);
	user->socket = accept(server->socket, (struct sockaddr*)&user->addr, &len);
	if (user->socket < 0)
	{
		perror("accept");
		free(user);
		return (false);
	}

	FD_SET(user->socket, &server->client.master);
	if (user->socket > server->client.fd_max)
		server->client.fd_max = user->socket;
	generate_guest_pseudo(user->nick, user->socket);
	server->client.fd_max = user->socket;

	// debug
	printf("[+] new connection from '%s' using socket '%d'\n", inet_ntoa(user->addr.sin_addr), user->socket);
	printf("\tgenerated nickname: '%s'\n", user->nick);

	push_new_user(&server->users, user);
	send_welcome(user->socket);

	return (true);
}

void	close_connection(t_server *server, int off)
{
	close(off);
	FD_CLR(off, &server->client.master);
	if (off == server->client.fd_max)
		server->client.fd_max -= 1;
	remove_user(&server->users, off);
}

bool	processing(t_server *server, int off)
{
	t_data	data;

	if (off == server->socket)
	{
		// new user
		accept_connection(server);
	}
	else
	{
		// received data
		_memset(&data, 0x0, sizeof(data));
		if (receive_data(off, &data, MAX_INPUT_LEN, 0) != true)
			close_connection(server, off);
		else
			interpreter(server, data, off);
	}
	return (true);
}

bool	running(t_server *server)
{
	int off;

	init_client_list(&server->client, server->socket);
	while (true)
	{
		server->client.read = server->client.master;
		if (select(server->client.fd_max + 1, &server->client.read, &server->client.write, NULL, NULL) < 0)
			return (false);
		off = 0;
		while (off <= server->client.fd_max)
		{
			if (FD_ISSET(off, &server->client.read))
				processing(server, off);
			off++;
		}
	}
	return (true);
}
