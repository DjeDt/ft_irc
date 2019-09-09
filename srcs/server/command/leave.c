/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:41:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:27:33 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	send_leave_notif(t_channel *chan, t_users *user)
{
	char			buf[MAX_INPUT_LEN + 3];
	t_channel_user	*tmp;

	printf("[LOG] '%s' leaved channel '%s'\n", user->nick, chan->name);
	snprintf(buf, MAX_INPUT_LEN, "[server] : '%s' leaved channel.", user->nick);
	tmp = chan->users;
	while (tmp != NULL)
	{
		circular_send(user->socket, buf);
		tmp = tmp->next;
	}
}

static void	_remove_user_from_channel(t_server *server, t_channel *chan, t_users *user, const char *chan_name)
{
	char buf[MAX_INPUT_LEN + 3];

	if (channel_user_remove(&chan->users, user) != true)
		return ;
	chan->num -= 1;
	user->chan = NULL;
	snprintf(buf, MAX_INPUT_LEN, "[server]: Disconnected from '%s'.", chan_name);
	circular_send(user->socket, buf);
	if (chan->num <= 0)
	{
		channel_delete(&server->channel, chan->name);
		return ;
	}
	send_leave_notif(chan, user);
}

void	irc_leave(t_server *server, t_users *user, char **command)
{
	t_channel	*chan;

	if (command[1] != NULL)
	{
		if (user->chan == NULL)
		{
			err_notonchannel(user, command[1]);
			return ;
		}
		chan = channel_search(&server->channel, command[1]);
		if (chan == NULL)
		{
			err_nosuchchannel(user, command[1]);
			return ;
		}
		if (user->chan != chan)
		{
			err_notonchannel(user, command[1]);
			return ;
		}
		_remove_user_from_channel(server, chan, user, command[1]);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
