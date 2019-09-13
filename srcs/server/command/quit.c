/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:16 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/13 17:21:44 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	notify_leave(t_users *user, char **command)
{
	int				len;
	char			buf[MAX_INPUT_LEN + 3];
	t_channel_user	*tmp;

	if (command[1] != NULL)
	{
		len = snprintf(buf, MAX_INPUT_LEN + 3, "[server] : '%s' quit: %s\r\n", user->nick.nick, command[1]);
		tmp = ((t_channel*)user->chan)->users;
		while (tmp != NULL)
		{
			circular_send(tmp->user->socket, buf, len);
			tmp = tmp->next;
		}
	}
	else
	{
		len = snprintf(buf, MAX_INPUT_LEN + 3, "Disconnected.\r\n");
		circular_send(user->socket, buf, len);
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
