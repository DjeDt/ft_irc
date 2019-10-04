/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:20:46 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/04 19:43:10 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool	create_server(t_server *server, struct addrinfo *base)
{
	struct addrinfo *ptr;

	ptr = base;
	while (ptr != NULL)
	{
		server->sock = socket(ptr->ai_family, \
								ptr->ai_socktype, ptr->ai_protocol);
		if (server->sock < 0)
			continue ;
		if (bind(server->sock, ptr->ai_addr, ptr->ai_addrlen) == 0)
			break ;
		close(server->sock);
		ptr = ptr->ai_next;
	}
	freeaddrinfo(base);
	if (ptr == NULL)
	{
		printf("[Log !] Can't bind address. abort\n");
		return (false);
	}
	return (true);
}

bool	initialize(t_server *server, const char *port)
{
	struct addrinfo	hints;
	struct addrinfo	*base;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(NULL, port, &hints, &base) != 0)
	{
		printf("[LOG !] Can't get address with %s.\n", port);
		return (false);
	}
	if (create_server(server, base) != true)
		return (false);
	if (listen(server->sock, MAX_QUEUE) < 0)
	{
		printf("[LOG !] Can't listen socket !\n");
		return (false);
	}
	init_kill_pass(server);
	return (true);
}
