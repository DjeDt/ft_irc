/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runnin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 23:02:55 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	init_client_list(t_fd *info, int socket)
{
	FD_ZERO(&info->master);
	FD_ZERO(&info->read);
	FD_ZERO(&info->write);
	FD_SET(socket, &info->master);
	info->fd_max = socket;
}

bool	accept_connection(t_server *server)
{
	socklen_t			len;
	t_users				*user;
	struct sockaddr_in	addr;

	if (!(user = user_create(0)))
		return (false);
	len = sizeof(addr);
	user->socket = accept(server->sock, (struct sockaddr*)&addr, &len);
	if (user->socket < 0)
	{
		printf("[LOG !] Error : can't accept new user");
		user_remove(&server->users, user->socket);
		return (false);
	}
	FD_SET(user->socket, &server->info.master);
	generate_guest_pseudo(user->nick, user->socket);
	if (user->socket > server->info.fd_max)
		server->info.fd_max = user->socket;
	user_push(&server->users, user);
	printf("[LOG +] new user : '%s'\n", user->nick);
	return (true);
}

void	close_connection(t_server *server, int off)
{
	t_users		*user;

	user = user_search_by_id(server->users, off);
	if (user == NULL)
		return ;
	close(user->socket);
	FD_CLR(off, &server->info.master);
	if (off == server->info.fd_max)
		server->info.fd_max -= 1;
	printf("[LOG -] Remove user '%s'\n", user->nick);
	channel_user_remove_full(server->channel, user);
	user_remove(&server->users, off);
}

bool	processing(t_server *server, int off)
{
	t_data	data;

	if (off == server->sock)
		accept_connection(server);
	else
	{
		_memset(&data, 0x0, sizeof(data));
		if (receive_data(off, &data) != true)
			close_connection(server, off);
		else
			interpreter(server, data, off);
	}
	return (true);
}

bool	running(t_server *server)
{
	int off;

	init_client_list(&server->info, server->sock);
	while (true)
	{
		off = 0;
		server->info.read = server->info.master;
		server->info.write = server->info.master;
		if (select(server->info.fd_max + 1, &server->info.read, &server->info.write, NULL, NULL) < 0)
			return (false);
		while (off <= server->info.fd_max)
		{
			if (FD_ISSET(off, &server->info.read))
				processing(server, off);
			off++;
		}
	}
	return (true);
}
