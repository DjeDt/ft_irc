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

	data.len = snprintf(data.data, MAX_INPUT_LEN, "'%s' is now known as '%s'.\n", user->nick, nick);
	_memset(user->nick, 0x0, MAX_NICK_LEN);
	memcpy(user->nick, nick, _strlen(nick));
	if (user->chan == NULL)
		send_data_to_single(user->socket, data.data, data.len);
	else
		notify_channel(user, data);
}

bool	is_available(t_users *users_list, t_users *user, char *nick, int size)
{
	t_users *tmp;

	tmp = users_list;
	while (tmp != NULL)
	{
		if (user->socket != tmp->socket)
		{
			if (strncmp(tmp->nick, nick, size > tmp->nick_len ? size : tmp->nick_len) == 0)
			{
				send_data_to_single(user->socket, "nickname already taken.\n", 24);
				return (false);
			}
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_nick(t_users *users_list, t_users *user, char *nick, int size)
{
	if (size < 1 || size > MAX_NICK_LEN)
	{
		send_data_to_single(user->socket, "nick must be between 1~13 char.\n", 32);
		return (false);
	}

	if (_memcmp(user->nick, nick, size > user->nick_len ? size : user->nick_len) == 0)
	{
		send_data_to_single(user->socket, "these are identical.\n", 21);
		return (false);
	}

	if (is_available(users_list, user, nick, size) != true)
		return (false);
	return (true);
}

void	irc_nick(t_server *server, t_users *user, char **command)
{
	if (command[1] != NULL)
	{
		if (check_nick(server->users, user, command[1], _strlen(command[1])) != true)
			return ;
		send_response(user, command[1]);
	}
	else
		send_data_to_single(user->socket, "usage '/nick <nickname>'.\n", 26);
}
