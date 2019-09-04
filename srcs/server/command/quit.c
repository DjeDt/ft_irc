/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:16 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:49:08 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	notify_leave(t_users *user, char **command)
{
	t_data			data;
	t_channel_user	*tmp;

	data.type = MESSAGE_CODE;
	data.err = false;

	if (command[1] != NULL)
	{
		data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : '%s' quit: %s", user->nick, command[1]);
		tmp = ((t_channel*)user->chan)->users;
		while (tmp != NULL)
		{
			send_data_to_single_user(tmp->user->socket, &data);
			tmp = tmp->next;
		}
	}
	else
	{
		data.len = snprintf(data.data, MAX_INPUT_LEN, "Disconnected.");
		send_data_to_single_user(user->socket, &data);
	}
}

void	irc_quit(t_server *server, t_users *user, char **command)
{
	if (server->users != NULL)
	{
		if (user != NULL)
		{
			notify_leave(user, command);
			channel_user_remove_full(server->channel, user);
			user_remove(&server->users, user->socket);
			close(user->socket);
			FD_CLR(user->socket, &server->info.master);
		}
	}
}
