/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:49:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 16:49:32 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_help(t_server *server, t_users *user, char **command)
{
	char	buf[MAX_INPUT_LEN + 3];

	(void)server;
	(void)command;
	snprintf(buf, MAX_INPUT_LEN + 3,						\
		"'/help'                : print this help\n"		\
		"'/nick <name>'         : change username\n"		\
		"'/list'                : list channel\n"			\
		"'/join <#chan>'        : join channel\n"			\
		"'/leave <#chan>'       : leave channel\n"			\
		"'/topic <topic>'       : show/set topic\n"			\
		"'/who'                 : list connected user\n"	\
		"'/msg <usr>'           : send message to user\n"	\
		"'/connect [ip <port>]' : connect to server\n"		\
		"'/quit'                : quit irc\n"				\
		"/kill'                 : shutdown connected server\r\n");

	if (FD_ISSET(user->socket, &server->info.write))
		circular_send(user->socket, buf);
//		send_data_to_single_user(user->socket, );
}
