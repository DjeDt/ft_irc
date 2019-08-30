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

	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : You aren't connected to any chan.");
	send_data_to_single(user->socket, data.data, data.len);
}

void	send_leave_notif(t_channel *chan, t_users *user)
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

static void	_remove_user_from_channel(t_channel *chan, t_users *user, const char *chan_name)
{
	t_data	data;

	if (chan == user->chan)
	{
		if (channel_user_remove(&chan->users, user) != true)
			return ;
		chan->num -= 1;
		printf("sjdfksdjhf ======= chan addr = %p\n", &chan);
		printf("leave users : %d\n", chan->num);

		user->chan = NULL;

		data.len = snprintf(data.data, MAX_INPUT_LEN, "[server] : Disconnected from '%s'.", chan_name);
		send_data_to_single(user->socket, data.data, data.len);

		printf("chan num = %d\n", chan->num);
		if (chan->num > 0)
			send_leave_notif(chan, user);
		else
			channel_delete(&chan, chan->name);
	}
	else
	{
		// toto better
		puts("not in channel");
	}
}


void	irc_leave(t_server *server, char **command, int off)
{
	t_users		*user;
	t_channel	*chan;


	puts("irc_leave");
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

		// search if user is in channel provided in command[]
		if (user->chan != NULL)
			_remove_user_from_channel(chan, user, command[1]);
	}
}
