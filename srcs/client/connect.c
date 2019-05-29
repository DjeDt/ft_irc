/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:34:53 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/28 14:53:29 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		is_valid_port(const char *port)
{
	int	ret;
	int count;

	count = 0;
	while (port[count] != '\0')
	{
		if (port[count] < '0' || port[count] > '9')
		{
//			error(INVALID_PORT, port);
			return (-1);
		}
		count++;
	}
	ret = atoi(port);
	return (ret);
}

in_addr_t	is_valid_ip(const char *ip)
{
	in_addr_t ret;

	ret = inet_addr(ip);
	if (ret == INADDR_NONE)
	{
//		error(INVALID_IP, ip);
		return (INADDR_NONE);
	}
	return (ret);
}

static int		init_socket_ipv4(t_list_user *user, in_addr_t ip, int port)
{
	socklen_t			len;

	len = sizeof(user->addr);
	user->socket = socket(PF_INET, SOCK_STREAM, 0);
	if (user->socket < 0)
	{
		// write on top box
//		printf("can't create socket using ipv4\n");
		return (false);
	}

	user->addr.sin_family = AF_INET;
	user->addr.sin_port = htons(port);
	user->addr.sin_addr.s_addr = ip;

	if (connect(user->socket, (struct sockaddr*)&user->addr, len) < 0)
	{
		return (false);
	}
	// write on top box
//	printf("Connected to %s using ipv4\n", inet_ntoa(user->addr.sin_addr));
	return (true);
}

bool	connect_to_server(t_list_user *user, const char *s_ip, const char *s_port)
{
	int			port;
	in_addr_t	ip;

	if ((ip = is_valid_ip(s_ip)) == INADDR_NONE)
		return (false);
	if ((port = is_valid_port(s_port)) < 0)
		return (false);
	if (init_socket_ipv4(user, ip, port) != true)
		return (false);
	return (true);
}
