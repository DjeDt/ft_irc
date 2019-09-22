/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:17:35 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/22 15:58:50 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static bool	check_name(char *name)
{
	int count;

	count = 1;
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
	int				len;
	char			buf[MAX_INPUT_LEN + CRLF];
	t_channel_user	*tmp;

	tmp = chan_users;
	len = snprintf(buf, MAX_INPUT_LEN + CRLF, JOIN_NOTIF,	\
		user->nick.nick, ((t_channel*)user->chan)->name);
	while (tmp != NULL)
	{
		if (user->socket != tmp->user->socket)
			circular_send(tmp->user->socket, buf, len);
		tmp = tmp->next;
	}
}

static void	notify_user(t_channel *chan, t_users *user)
{
	char			buf[MAX_INPUT_LEN + CRLF];
	t_channel_user	*tmp;

	if (chan->topic[0] != '\0')
		rpl_topic(chan, user);
	else
		rpl_notopic(chan, user);
	tmp = chan->users;
	while (tmp != NULL)
	{
		ft_memset(buf, 0x0, MAX_INPUT_LEN + CRLF);
		rpl_namreply(chan, user, tmp->user->nick.nick, buf);
		tmp = tmp->next;
	}
	ft_memset(buf, 0x0, MAX_INPUT_LEN + CRLF);
	rpl_endofnames(chan, user, buf);
}

static void manage_user_join(t_server *server, t_users *user, char *chan_name)
{
	t_channel *chan;

	chan = channel_search(&server->channel, chan_name);
	if (chan != NULL)
	{
		chan->num += 1;
		user->chan = chan;
		channel_user_add(&chan->users, user);
		notify_user(chan, user);
		notify_channel(chan->users, user);
	}
	else
	{
		chan = channel_add(&server->channel, chan_name);
		if (chan == NULL)
			return ;
		chan->num += 1;
		user->chan = chan;
		channel_user_add(&chan->users, user);
		notify_user(chan, user);
	}
}

void		irc_join(t_server *server, t_users *user, char **command)
{
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
		manage_user_join(server, user, command[1]);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
