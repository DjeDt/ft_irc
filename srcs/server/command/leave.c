/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:41:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 21:07:19 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	user_not_connected(t_users *user)
{
	t_data data;

	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : You aren't connected to any chan.");
	send_data_to_single(user->socket, data.data, data.len);
}

static void	send_leave_notif(t_channel *chan, t_users *user)
{
	t_data			data;
	t_channel_user	*tmp;

	printf("'%s' leaved channel '%s'\n", user->nick, chan->name);
	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : '%s' leaved the channel.\n", user->nick);
	tmp = chan->users;
	while (tmp != NULL)
	{
		send_data_to_single(tmp->user->socket, data.data, data.len);
		tmp = tmp->next;
	}
}

static void	channel_doesnt_exist(t_users *user, char *chan_name)
{
	t_data data;

	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : channel '%s' doesn't exist.", chan_name);
	send_data_to_single(user->socket, data.data, data.len);
}

static void	user_not_in_channel(t_channel *chan, t_users *user)
{
	t_data data;

	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : You are not connected to '%s'.", chan->name);
	send_data_to_single(user->socket, data.data, data.len);
}

static void	_remove_user_from_channel(t_server *server, t_channel *chan, t_users *user, const char *chan_name)
{
	t_data	data;

	if (channel_user_remove(&chan->users, user) != true)
		return ;
	chan->num -= 1;
	user->chan = NULL;

	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : Disconnected from '%s'.", chan_name);
	send_data_to_single(user->socket, data.data, data.len);
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
			user_not_connected(user);
			return ;
		}
		chan = channel_search(&server->channel, command[1]);
		if (chan == NULL)
		{
			channel_doesnt_exist(user, command[1]);
			return ;
		}
		if (user->chan != NULL && user->chan == chan)
			_remove_user_from_channel(server, chan, user, command[1]);
		else
			user_not_in_channel(chan, user);
	}
}
