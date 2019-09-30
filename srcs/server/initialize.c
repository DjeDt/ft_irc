/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:20:46 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/30 14:48:11 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static bool	prepare_data(t_server *server, void *addr, int type)
{
	if (type == IPV4_TYPE)
	{
		server->sock = socket(PF_INET, SOCK_STREAM, 0);
		if (server->sock < 0)
		{
			printf("[LOG !] Can't create socket using ipv4\n");
			return (false);
		}
		((struct sockaddr_in*)addr)->sin_family = AF_INET;
		((struct sockaddr_in*)addr)->sin_addr.s_addr = htonl(INADDR_ANY);
		((struct sockaddr_in*)addr)->sin_port = htons(server->port);
	}
	else if (type == IPV6_TYPE)
	{
		server->sock = socket(PF_INET6, SOCK_STREAM, 0);
		if (server->sock < 0)
		{
			printf("[LOG !] Can't create socket using ipv6\n");
			return (false);
		}
		((struct sockaddr_in6*)addr)->sin6_family = AF_INET6;
		((struct sockaddr_in6*)addr)->sin6_addr = in6addr_any;
		((struct sockaddr_in6*)addr)->sin6_port = htons(server->port);
	}
	return (true);
}

static bool	bind_socket_ipv4(t_server *server)
{
	struct sockaddr_in adr;

	if (prepare_data(server, &adr, IPV4_TYPE) != true)
		return (false);
	if (bind(server->sock, (struct sockaddr*)&adr, sizeof(struct sockaddr)) < 0)
	{
		printf("[LOG !] Can't bind socket to address using ipv4\n");
		return (false);
	}
	printf("[LOG !] Socket correctly setup using ipv4\n");
	return (true);
}

static bool	bind_socket_ipv6(t_server *server)
{
	struct sockaddr_in6 adr;

	if (prepare_data(server, &adr, IPV6_TYPE) != true)
		return (false);
	if (bind(server->sock, (struct sockaddr*)&adr, sizeof(struct sockaddr)) < 0)
	{
		printf("[LOG !] Can't bind socket to address using ipv6\n");
		return (false);
	}
	printf("[LOG !] Socket correctly setup using ipv6\n");
	return (false);
}

static bool	init_socket(t_server *server, const char *port)
{
	server->port = ft_atoi(port);
	if (server->port < 1)
	{
		printf("Error: '%s' port is invalid. Abort\n", port);
		return (false);
	}
	if (bind_socket_ipv4(server) != true)
	{
		if (bind_socket_ipv6(server) != true)
			return (false);
	}
	if (listen(server->sock, MAX_QUEUE) < 0)
	{
		printf("[LOG !] Can't listen socket !\n");
		return (false);
	}
	return (true);
}

bool		initialize(t_server *server, const char *port)
{
	ft_memset(server, 0x0, sizeof(t_server));
	if (init_socket(server, port) != true)
		return (false);
	return (true);
}
