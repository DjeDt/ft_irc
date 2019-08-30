/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:17:35 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 21:13:58 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	already_in_chan(t_users *user)
{
	t_data		data;
	t_channel	*chan;

	chan = (t_channel*)user->chan;
	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : Already connected to '%s' channel.", chan->name);
	send_data_to_single(user->socket, data.data, data.len);
}

static void	accept_user(t_channel *channel, t_users *user)
{
	t_data			data;
	t_channel_user	*tmp;

	if (user->chan == NULL)
	{
		puts("accept user");

		channel->num += 1;
		user->chan = channel;
		channel_user_add(&channel->users, user);
		data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : '%s' joined.", user->nick);

		tmp = channel->users;
		while (tmp != NULL)
		{
			if (user->socket != tmp->user->socket)
				send_data_to_single(tmp->user->socket, data.data, data.len);
			tmp = tmp->next;
		}
	}
}

static void	init_channel(t_server *server, t_users *user, char *chan_name)
{
	t_data		data;
	t_channel	*chan;

	puts("init channel");

	chan = channel_add(&server->channel, chan_name);
	if (chan == NULL)
		return ;

	chan->num += 1;
	user->chan = chan;

	channel_user_add(&chan->users, user);

	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : you joined '%s' channel.\n", chan_name);
	send_data_to_single(user->socket, data.data, data.len);
}

void	irc_join(t_server *server, char **command, int off)
{
	t_users		*user;
	t_channel	*channel;

	if (command[1] != NULL)
	{
		puts("irc_join");

		user = user_search_by_id(server->users, off);
		if (user == NULL)
			return ;

		if (user->chan != NULL)
		{
			already_in_chan(user);
			return ;
		}

		channel = channel_search(server->channel, command[1]);
		if (channel == NULL)
			init_channel(server, user, command[1]);
		else
			accept_user(channel, user);
	}
}
