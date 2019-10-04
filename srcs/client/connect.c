/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:34:53 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/04 19:45:26 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static bool	connect_to_server(t_user *user, struct addrinfo *base)
{
	struct addrinfo *ptr;

	ptr = base;
	while (ptr != NULL)
	{
		user->socket = socket(ptr->ai_family, \
								ptr->ai_socktype, ptr->ai_protocol);
		if (user->socket < 0)
			continue ;
		if (connect(user->socket, ptr->ai_addr, ptr->ai_addrlen) != -1)
			break ;
		close(user->socket);
		ptr = ptr->ai_next;
	}
	freeaddrinfo(base);
	if (ptr == NULL)
		return (false);
	return (true);
}

bool		irc_connect(t_interface *inter, t_user *user, char *ip, char *port)
{
	struct addrinfo hints;
	struct addrinfo *base;

	ft_memset(&hints, 0x0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(ip, port, &hints, &base) != 0)
		return (false);
	if (connect_to_server(user, base) != true)
		return (false);
	user->connected = true;
	refresh_top_interface(inter, "Connected to %s/%s !", ip, port);
	return (true);
}

void		wrapper_connect(t_interface *inter, t_user *user, char **cmd)
{
	bool ret;

	ret = false;
	if (user->connected != true)
	{
		if (cmd[1] == NULL)
			refresh_top_interface(inter, "error: %s [ip <port>]", cmd[0]);
		else if (cmd[2] == NULL)
		{
			refresh_top_interface(inter, BASIC_PORT_STR, cmd[1], DEFAULT_PORT);
			ret = irc_connect(inter, user, cmd[1], DEFAULT_PORT);
		}
		else
			ret = irc_connect(inter, user, cmd[1], cmd[2]);
		if (ret == false)
			refresh_top_interface(inter, "Can't connect to %s:%s.", \
									cmd[1], cmd[2]);
	}
	else
		refresh_top_interface(inter, "you are already connected.");
}
