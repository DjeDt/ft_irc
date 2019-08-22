/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:43:26 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 16:30:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	notify_channel(t_users *user, t_data data)
{
	t_channel		*chan;
	t_channel_user	*tmp;

	chan = user->chan;
	tmp = chan->users;
	while (tmp != NULL)
	{
		send_data_to_single(tmp->user->socket, data.data, data.len);
		tmp = tmp->next;
	}

}

void	send_response(t_users *user, char *nick)
{
	t_data			data;

	data.len = snprintf(data.data, MAX_INPUT_LEN, "'%s' changed nick to : '%s'.\n", user->nick, nick);
	_memset(user->nick, 0x0, MAX_NICK_LEN);
	memcpy(user->nick, nick, _strlen(nick));
	if (user->chan == NULL)
		send_data_to_single(user->socket, data.data, data.len);
	else
		notify_channel(user, data);
}

bool	is_available(t_users *users, char *nick, int off)
{
	t_users *tmp;

	tmp = users;
	while (tmp != NULL)
	{
		if (off != tmp->socket)
		{
			if (strncmp(tmp->nick, nick, MAX_NICK_LEN) == 0)
			{
				send_data_to_single(off, "nickname already taken.\n", 24);
				return (false);
			}
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_nick(t_users *users, t_users *usr, char *nick, int off)
{
	int		size;

	size = _strlen(nick);
	printf("user->nick = '%s' | command = '%s' | size = '%d'\n", usr->nick, nick, size);
	if (size < 1 || size > MAX_NICK_LEN)
	{
		send_data_to_single(off, "nick must be between 1~13 char.\n", 32);
		return (false);
	}
	if (strncmp(usr->nick, nick, MAX_NICK_LEN) == 0)
	{
		send_data_to_single(off, "these are identical.\n", 21);
		return (false);
	}
	if (is_available(users, nick, off) != true)
		return (false);
	return (true);
}

void	irc_nick(t_server *server, char **command, int off)
{
	t_users	*user;

	if (command[1] != NULL)
	{
		if ((user = user_search_by_id(server->users, off)) == NULL)
			return ;
		if (check_nick(server->users, user, command[1], off) != true)
			return ;
		send_response(user, command[1]);
	}
	else
		send_data_to_single(off, "usage '/nick <nickname>'.\n", 26);
}
