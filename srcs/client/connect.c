/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:34:53 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/02 13:43:42 by ddinaut          ###   ########.fr       */
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
		return (-1);
	return (ret);
}

static int			init_socket_ipv4(t_user *user, in_addr_t ip, int port)
{
	socklen_t			len;
	struct sockaddr_in	addr;


	//debug ipv6
//	return (false);

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

static bool			init_socket_ipv6(t_interface *inter, t_user *user, const char *ip, int port)
{
	socklen_t			len;
	struct sockaddr_in6	addr;

	len = sizeof(addr);
	user->socket = socket(AF_INET6, SOCK_STREAM, 0);
	refresh_top_interface(inter, "socket : %s", strerror(errno));
	if (user->socket < 0)
		return (false);
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(port);
	refresh_top_interface(inter, "htons : %s", strerror(errno));
	inet_pton(AF_INET6, ip, &addr.sin6_addr);
	refresh_top_interface(inter, "inet pton : %s", strerror(errno));
	if (connect(user->socket, (struct sockaddr*)&addr, len) < 0)
	{
		refresh_top_interface(inter, "connect : %s", strerror(errno));
		return (false);
	}
	return (true);
}

bool				irc_connect(t_interface *inter, t_user *user, \
								const char *s_ip, const char *s_port)
{
	int			port;
	in_addr_t	ip;

//	ip = is_valid_ip(s_ip, ft_strlen(s_ip));
	if ((ip = is_valid_ip(s_ip, ft_strlen(s_ip))) == INADDR_NONE)
	{
		refresh_top_interface(inter, "can't connect to '%s', bad ip.", s_ip);
		return (false);
	}
	if ((port = is_valid_port(s_port)) < 0)
	{
		refresh_top_interface(inter, "can't connect to %s/%s. bad port", s_ip, s_port);
		return (false);
	}

	if (init_socket_ipv4(user, ip, port) != true)
	{
		if (init_socket_ipv6(inter, user, s_ip, port) != true)
			refresh_top_interface(inter, "can't connect to '%s' using ipv4/ipv6. [%s]", s_ip, strerror(errno));
		return (false);
	}
	refresh_top_interface(inter, "Connected to %s/%s !", s_ip, s_port);
	user->connected = true;
	return (true);
}

void				wrapper_connect(t_interface *inter, \
									t_user *user, char **cmd)
{
	if (user->connected != true)
	{
		if (cmd[1] == NULL)
			refresh_top_interface(inter, "error: /connect [ip <port>]");
		else if (cmd[2] == NULL)
		{
			refresh_top_interface(inter, BASIC_PORT_STR, cmd[1], DEFAULT_PORT);
			irc_connect(inter, user, cmd[1], DEFAULT_PORT);
		}
		else
			irc_connect(inter, user, cmd[1], cmd[2]);
	}
	else
		refresh_top_interface(inter, "you are already connected.");
}
