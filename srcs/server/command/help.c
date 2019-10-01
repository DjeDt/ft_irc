/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:49:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/01 13:13:44 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_help(t_server *server, t_users *user, char **command)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	(void)server;
	(void)command;
	len = snprintf(buf, MAX_INPUT_LEN + CRLF, \
		"/help                : print this help\r\n"		\
		"/nick <name>         : change username\r\n"		\
		"/list [chan]         : list channel\r\n"			\
		"/join <chan>         : join channel\r\n"			\
		"/leave <chan>        : leave channel\r\n"			\
		"/topic <chan [topic]>: show/set topic\r\n"			\
		"/who [chan]          : list connected user\r\n"	\
		"/msg <usr> <message> : send message to user\r\n"	\
		"/connect <ip [port]> : connect to server\r\n"		\
		"/quit                : quit irc\r\n"				\
		"/kill [passwd]       : shutdown connected server\r\n");
	if (FD_ISSET(user->socket, &server->info.write))
		circular_send(user->socket, buf, len);
}
