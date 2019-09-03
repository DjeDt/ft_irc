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
	t_data data;

	(void)server;
	(void)command;
	data.type = MESSAGE_CODE;
	data.err = false;
	data.len = snprintf(data.data, MAX_INPUT_LEN, \
		"'/help'                : print this help\n" \
		"'/nick <name>'         : change username\n" \
		"'/list'                : list channel\n" \
		"'/join <chan>'         : join channel\n" \
		"'/leave <chan>'        : leave channel\n" \
		"'/who'                 : list connected user\n" \
		"'/msg <usr>'           : send message to user\n" \
		"'/connect [ip <port>]' : connect to server\n" \
		"'/quit'                : quit irc\n" \
		"/shutdown'             : shutdown connected server\n");

	if (FD_ISSET(user->socket, &server->info.write))
		send_data_to_single_user(user->socket, &data);
}
