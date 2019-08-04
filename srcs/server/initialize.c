/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:20:46 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 16:18:42 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static bool	init_socket_ipv4(t_server *server, struct sockaddr_in addr)
{
	server->sock = socket(PF_INET, SOCK_STREAM, 0);
	if (server->sock < 0)
	{
		error(INVALID_SCKT, "can't create socket using ipv4");
		return (false);
	}

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(server->port);

	if (bind(server->sock, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0)
	{
		error(INVALID_BIND, "can't bind socket to address using ipv4");
		return (false);
	}
	logger("socket correctly setup using ipv4", stdout);
	return (true);
}

// TODO
bool	init_socket_ipv6(t_server *server, struct sockaddr_in addr)
{
	server->sock = socket(PF_INET6, SOCK_STREAM, 0);
	if (server->sock < 0)
	{
		error(INVALID_SCKT, "can't create socket using ipv6");
		return (false);
	}
	addr.sin_family = AF_INET6;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(server->port);
	if (bind(server->sock, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0)
	{
		error(INVALID_BIND, "can't bind socket to address using ipv6");
		return (false);
	}
	logger("socket correctly setup using ipv6", stdout);
	return (false);
}

static bool	init_socket(t_server *server, const char *port)
{
	socklen_t			len;
	struct sockaddr_in	addr;

	len = sizeof(addr);
	_memset(&addr, 0x0, len);
	server->port = atoi(port);
	if (server->port < 1)
	{
		error(INVALID_PORT, port);
		return (false);
	}

	/* ipv4 / ipv6 */
	if (init_socket_ipv4(server, addr) != true)
		return (false);

	if (listen(server->sock, MAX_QUEUE) < 0)
	{
		error(INVALID_LISTEN, strerror(errno));
		return (false);
	}
	return (true);
}

bool	initialize(t_server *server, const char *port)
{
	_memset(server, 0x0, sizeof(t_server));
	if (init_socket(server, port) != true)
		return (false);

	return (true);
}
