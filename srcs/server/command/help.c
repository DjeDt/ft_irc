/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:49:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/30 16:12:26 by Dje              ###   ########.fr       */
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
		"/list                : list channel\r\n"			\
		"/join <#chan>        : join channel\r\n"			\
		"/leave <#chan>       : leave channel\r\n"			\
		"/topic <topic>       : show/set topic\r\n"			\
		"/who                 : list connected user\r\n"	\
		"/msg <usr>           : send message to user\r\n"	\
		"/connect [ip <port>] : connect to server\r\n"		\
		"/quit                : quit irc\r\n"				\
		"/kill                : shutdown connected server\r\n");
	if (FD_ISSET(user->socket, &server->info.write))
		circular_send(user->socket, buf, len);
}
