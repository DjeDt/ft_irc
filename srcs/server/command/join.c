/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:17:35 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:02:35 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static bool	check_name(char *name)
{
	int count;

	count = 1;
	printf("name = %s\n", name);
	if (name[0] != '#' && name[0] != '&')
		return (false);
	while (name[count] != '\0')
	{
		if (name[count] == ' ' || name[count] == 7 || name[count] == ',')
			return (false);
		count++;
	}
	return (true);
}

static void	notify_channel(t_channel_user *chan_users, t_users *user)
{
	char			buf[MAX_INPUT_LEN + 3];
	t_channel_user	*tmp;

	tmp = chan_users;
	snprintf(buf, MAX_INPUT_LEN, "[server] : '%s' joined channel.", user->nick);
	while (tmp != NULL)
	{
		if (user->socket != tmp->user->socket)
			circular_send(user->socket, buf);
		tmp = tmp->next;
	}
}

static void	notify_user(t_channel *chan, t_users *user)
{
	char			buf[MAX_INPUT_LEN + 3];
	t_channel_user	*tmp;

	if (chan->topic != NULL)
		rpl_topic(chan, user);
	else
		rpl_notopic(chan, user);

	tmp = chan->users;
	while (tmp != NULL)
	{
		rpl_namreply(chan, user, buf, tmp->user->nick);
		tmp = tmp->next;
	}
	rpl_endofnames(chan, user, buf);
}

static void	accept_user(t_channel *channel, t_users *user)
{
	if (user->chan == NULL)
	{
		channel->num += 1;
		user->chan = channel;
		channel_user_add(&channel->users, user);
		notify_user(channel, user);
		notify_channel(channel->users, user);
	}
}

static void	init_channel(t_server *server, t_users *user, char *chan_name)
{
	t_channel		*chan;

	chan = channel_add(&server->channel, chan_name);
	if (chan == NULL)
		return ;
	chan->num += 1;
	user->chan = chan;
	channel_user_add(&chan->users, user);
	notify_user(chan, user);
}

void	irc_join(t_server *server, t_users *user, char **command)
{
	t_channel	*channel;

	if (command[1] != NULL)
	{
		if (check_name(command[1]) == false)
		{
			err_erroneuschanname(user, command[1]);
			return ;
		}
		if (user->chan != NULL)
		{
			err_toomanychannels(user, command[1]);
			return ;
		}
		channel = channel_search(&server->channel, command[1]);
		if (channel == NULL)
			init_channel(server, user, command[1]);
		else
			accept_user(channel, user);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
