/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:41:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/01 16:02:45 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	send_leave_notif(t_channel *chan, t_users *user)
{
	int				len;
	char			buf[MAX_INPUT_LEN + CRLF];
	t_channel_user	*tmp;

	printf("[LOG] '%s' leaved channel '%s'\n", user->nick.nick, chan->name);
	len = snprintf(buf, MAX_INPUT_LEN + CRLF, LEAVE_NOTIF, user->nick.nick);
	tmp = chan->users;
	while (tmp != NULL)
	{
		if (user->socket != tmp->user->socket)
			circular_send(tmp->user->socket, buf, len);
		tmp = tmp->next;
	}
}

static void	leave_remove_user_from_channel \
	(t_server *server, t_channel *chan, t_users *user, const char *chan_name)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	if (channel_user_remove(&chan->users, user) != true)
		return ;
	chan->num -= 1;
	user->chan = NULL;
	len = snprintf(buf, MAX_INPUT_LEN + CRLF, LEAVE_CHAN, chan_name);
	circular_send(user->socket, buf, len);
	if (chan->num <= 0)
	{
		channel_delete(&server->channel, chan->name);
		return ;
	}
	send_leave_notif(chan, user);
}

static bool	check_param(t_users *user, t_channel *chan, char *command)
{
	if (user->chan == NULL)
	{
		err_notonchannel(user, command);
		return (false);
	}
	if (chan == NULL)
	{
		err_nosuchchannel(user, command);
		return (false);
	}
	if (user->chan != chan)
	{
		err_notonchannel(user, command);
		return (false);
	}
	return (true);
}

void		irc_leave(t_server *server, t_users *user, char **command)
{
	t_channel	*chan;

	chan = NULL;
	if (command[1] != NULL)
	{
		if (command[2] != NULL)
		{
			err_toomanyarguments(user, command[0]);
			return ;
		}
		chan = channel_search(&server->channel, command[1]);
		if (check_param(user, chan, command[1]) != true)
			return ;
		leave_remove_user_from_channel(server, chan, user, command[1]);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
