/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:49:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/06/07 15:12:31 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_help(t_server *server, t_users *user, char **command)
{
	char help[] =
		"'/help' : print this help\n"
		"'/nick <name>' : change username\n"
		"'/list' : list channel\n"
		"'/join <chan>' : join channel\n"
		"'/leave <chan>' : leave channel\n"
		"'/who' : list connected user\n"
		"'/msg <usr>' : send message to user\n"
		"'/connect [ip <port>]' : connect to server\n"
		"'/quit' : quit irc\n"
		"/shutdown' : shutdown connected server\n";

	(void)server;
	(void)command;
	if (FD_ISSET(user->socket, &server->info.write))
		send_data_to_single(user->socket, help, sizeof(help));
	printf("HELP\n");
}
