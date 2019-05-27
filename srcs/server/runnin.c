/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runnin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/26 22:35:40 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root != NULL)
	{
		btree_apply_infix(root->left, applyf);
		applyf(root->data.nick);
		btree_apply_infix(root->right, applyf);
	}
}

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
	t_user		user;
	socklen_t	addr_len;

	addr_len = sizeof(user.addr);
	user.socket = accept(server->socket, (struct sockaddr*)&user.addr, &addr_len);
	if (user.socket < 0)
	{
		perror("accept");
		return (false);
	}
	else
	{
		printf("[+] new connection from '%s' set to socket %d\n", inet_ntoa(user.addr.sin_addr), user.socket);
		FD_SET(user.socket, &client->master);
		if (user.socket > client->fd_max)
			client->fd_max = user.socket;
		btree_insert_data_int(&server->users, user, intcmp);
//		btree_apply_infix(server->users, (void*)&puts);
	}
	return (true);
}

void	print_int(int *data)
{
	printf("deleted socket %d\n", *data);
}

bool	processing(t_server *server)
{
	int		off;
	t_data	data;

	off = 0;
	while (off <= server->client.fd_max)
	{
		if (FD_ISSET(off, &server->client.read))
		{
			if (off == server->socket)
			{
				accept_connection(server, &server->client);
				// check is false
			}
			else
			{
				if (receive_data(server, &data, off) != true)
					btree_delete_node_int(&server->users, off);
				btree_apply_infix(server->users, (void*)&print_int);

					//remove_user(&server->users, off);
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
