/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:41:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 16:55:43 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	send_leave_notif(t_channel *chan, t_users *user)
{
	int				len;
	char			buf[MAX_INPUT_LEN + 3];
	t_channel_user	*tmp;

	printf("[LOG] '%s' leaved channel '%s'\n", user->nick.nick, chan->name);
	len = snprintf(buf, MAX_INPUT_LEN + 3, "[server] : '%s' leaved channel.%s", user->nick.nick, CRLF);
	tmp = chan->users;
	while (tmp != NULL)
	{
		circular_send(user->socket, buf, len);
		tmp = tmp->next;
	}
}

static void	_remove_user_from_channel(t_server *server, t_channel *chan, t_users *user, const char *chan_name)
{
	int		len;
	char	buf[MAX_INPUT_LEN + 3];

	if (channel_user_remove(&chan->users, user) != true)
		return ;
	chan->num -= 1;
	user->chan = NULL;
	len = snprintf(buf, MAX_INPUT_LEN + 3, "[server]: Disconnected from '%s'.%s", chan_name, CRLF);
	circular_send(user->socket, buf, len);
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
