/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:34:53 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/12 21:10:17 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int			is_valid_port(const char *port)
{
	int ret;
	int count;

	count = 0;
	while (port[count] != '\0')
	{
		if (port[count] < '0' || port[count] > '9')
			return (-1);
		count++;
	}
	ret = ft_atoi(port);
	return (ret);
}

static in_addr_t	is_valid_ip(const char *ip, int len)
{
	in_addr_t	ret;

	if (ft_strncmp(ip, "localhost", len > 9 ? len : 9) == 0)
		ret = inet_addr(LOCALHOST);
	else
		ret = inet_addr(ip);
	if (ret == INADDR_NONE)
		return (INADDR_NONE);
	return (ret);
}

static int			init_socket_ipv4(t_list_user *user, in_addr_t ip, int port)
{
	socklen_t			len;
	struct sockaddr_in	addr;

	len = sizeof(addr);
	user->socket = socket(PF_INET, SOCK_STREAM, 0);
	if (user->socket < 0)
		return (false);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = ip;

	if (connect(user->socket, (struct sockaddr*)&addr, len) < 0)
		return (false);
	return (true);
}

bool				irc_connect(t_interface *inter, t_list_user *user, const char *s_ip, const char *s_port)
{
	int			port;
	in_addr_t	ip;

	if ((ip = is_valid_ip(s_ip, ft_strlen(s_ip))) == INADDR_NONE)
	{
		refresh_top_interface(inter, "can't connect to '%s'.", s_ip);
		return (false);
	}

	if ((port = is_valid_port(s_port)) < 0)
	{
		refresh_top_interface(inter, "can't connect to %s/%s.", s_ip, s_port);
		return (false);
	}

	if (init_socket_ipv4(user, ip, port) != true)
	{
		refresh_top_interface(inter, "can't connect to '%s' using ipv4.", s_ip);
		return (false);
	}
	refresh_top_interface(inter, "Connected to %s/%s !", s_ip, s_port);
	user->connected = true;
	return (true);
}

void				wrapper_connect(t_interface *inter, t_list_user *user, char **command)
{
	if (user->connected != true)
	{
		if (command[1] == NULL)
			refresh_top_interface(inter, "error: /connect [ip <port>]");
		else if (command[2] == NULL)
		{
			refresh_top_interface(inter, "Connecting to '%s' using default port '%s'", command[1], DEFAULT_PORT);
			irc_connect(inter, user, command[1], DEFAULT_PORT);
		}
		else
			irc_connect(inter, user, command[1], command[2]);
	}
	else
		refresh_top_interface(inter, "you are already connected. use '/disconnect' first");
}
