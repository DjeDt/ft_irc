/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runnin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/13 17:39:34 by ddinaut          ###   ########.fr       */
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
	generate_guest_pseudo(user->nick.nick, user->socket);
	if (user->socket > server->info.fd_max)
		server->info.fd_max = user->socket;
	user_push(&server->users, user);
	printf("[LOG +] new user : '%s'\n", user->nick.nick);
	return (true);
}

void	close_connection(t_server *server, t_users *user)
{
	char trash[MAX_INPUT_LEN];

	if (user->socket == server->info.fd_max)
		server->info.fd_max -= 1;
	printf("[LOG -] Remove user '%s'\n", user->nick.nick);
	while (true)
	{
		if (recv(user->socket, trash, MAX_INPUT_LEN, 0) < 1)
			break ;
	}
	close(user->socket);
	FD_CLR(user->socket, &server->info.master);
	channel_user_remove_full(&server->channel, user);
	user_remove(&server->users, user->socket);
}


void	processing(t_server *server, int socket)
{
	t_users	*user;

	if (socket == server->sock)
	{
		accept_connection(server);
		return ;
	}
	user = user_search_by_id(server->users, socket);
	if (user == NULL)
		return ;
	if (circular_get(user) == false)
	{
		close_connection(server, user);
		return ;
	}
	while (search_for_crlf(user->circ.buf, user->circ.head, user->circ.len) == true ||
		user->circ.len >= MAX_INPUT_LEN)
	{
		interpreter(server, user);
	}
}

bool	running(t_server *server)
{
	int socket;

	init_client_list(&server->info, server->sock);
	while (true)
	{
		socket = 0;
		server->info.read = server->info.master;
		server->info.write = server->info.master;
		if (select(server->info.fd_max + 1, &server->info.read, &server->info.write, NULL, NULL) < 0)
			return (false);
		while (socket <= server->info.fd_max)
		{
			if (FD_ISSET(socket, &server->info.read))
				processing(server, socket);
			socket++;
		}
	}
	return (true);
}
