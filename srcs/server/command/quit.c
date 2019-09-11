/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:16 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 16:56:46 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	notify_leave(t_users *user, char **command)
{
	char			buf[MAX_INPUT_LEN + 3];
	t_channel_user	*tmp;

	if (command[1] != NULL)
	{
		snprintf(buf, MAX_INPUT_LEN, "[server] : '%s' quit: %s", user->nick, command[1]);
		tmp = ((t_channel*)user->chan)->users;
		while (tmp != NULL)
		{
			circular_send(tmp->user->socket, buf, _strlen(buf));
			tmp = tmp->next;
		}
	}
	else
	{
		snprintf(buf, MAX_INPUT_LEN, "Disconnected.");
		circular_send(user->socket, buf, _strlen(buf));
	}
}

void	irc_quit(t_server *server, t_users *user, char **command)
{
	if (server->users != NULL)
	{
		if (user != NULL)
		{
			notify_leave(user, command);
			channel_user_remove_full(&server->channel, user);
			user_remove(&server->users, user->socket);
			close(user->socket);
			FD_CLR(user->socket, &server->info.master);
		}
	}
}
