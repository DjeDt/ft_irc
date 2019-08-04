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

void	user_not_connected(t_users *user)
{
	t_data data;

	data.len = snprintf(data.data, MAX_INPUT_LEN, "You aren't connected to any chan.");
	send_data_to_single(user->socket, data.data, data.len);
}

void	send_leave_notif(t_channel *chan, t_users *user)
{
	t_data			data;
	t_channel_user	*tmp;

	printf("'%s' leaved channel '%s'\n", user->nick, chan->name);
	data.len = snprintf(data.data, MAX_INPUT_LEN, "'%s' leaved the channel.\n", user->nick);
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

	data.len = snprintf(data.data, MAX_INPUT_LEN, "channel '%s' doesn't exist.", chan_name);
	send_data_to_single(user->socket, data.data, data.len);
}

static void	_remove_user_from_channel(t_channel *chan, t_users *user, const char *chan_name)
{
	t_data	data;

	if (chan == user->chan)
	{
		if (channel_user_remove(&chan->users, user) != true)
			return ;
		chan->num -= 1;
		user->chan = NULL;
		data.len = snprintf(data.data, MAX_INPUT_LEN, "Disconnected from '%s'.", chan_name);
		send_data_to_single(user->socket, data.data, data.len);
		if (chan->num == 0)
			channel_delete(&chan, chan->name);
		else
			send_leave_notif(chan, user);
	}
}


void	irc_leave(t_server *server, char **command, int off)
{
	t_users		*user;
	t_channel	*chan;

	if (command[1] != NULL)
	{
		user = user_search_by_id(server->users, off);
		if (user == NULL)
			return ;
		if (user->chan == NULL)
		{
			user_not_connected(user);
			return ;
		}
		chan = channel_search(server->channel, command[1]);
		if (chan == NULL)
		{
			channel_doesnt_exist(user, command[1]);
			return ;
		}

		if (user->chan != NULL)
			_remove_user_from_channel(chan, user, command[1]);
	}
}