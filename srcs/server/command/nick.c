/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:43:26 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 20:12:34 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool	is_available(t_users *users_list, t_users *user, char *nick, int size)
{
	t_users *tmp;

	tmp = users_list;
	while (tmp != NULL)
	{
		if (user->socket != tmp->socket)
		{
			if (strncmp(tmp->nick, nick, size > tmp->nick_len ? size : tmp->nick_len) == 0)
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	check_nick(t_users *users_list, t_users *user, char *nick, int size)
{
	if (size < 1 || size > MAX_NICK_LEN)
	{
		err_erroneusnickname(user, nick);
		return (false);
	}

	if (is_available(users_list, user, nick, size) != true)
	{
		err_nicknameinuse(user, nick);
		return (false);
	}
	return (true);
}

void	send_response(t_users *user)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, "You are now known as '%s'.", user->nick);
	circular_send(user->socket, buf);
}

void	notify_channel(t_users *user, char *old_nick)
{
	char			buf[MAX_INPUT_LEN + 3];
	t_channel_user	*tmp;

	if (user->chan != NULL)
	{
		snprintf(buf, MAX_INPUT_LEN, "'%s' is now known as '%s'.", old_nick, user->nick);
		tmp = ((t_channel*)user->chan)->users;
		while (tmp != NULL)
		{
			if (tmp->user->socket != user->socket)
				circular_send(user->socket, buf);
			tmp = tmp->next;
		}
	}
}

void	irc_nick(t_server *server, t_users *user, char **command)
{
	int		size;
	char	old_nick[MAX_NICK_LEN + 1];

	if (command[1] != NULL)
	{
		size = _strlen(command[1]);
		if (check_nick(server->users, user, command[1], size) != true)
			return ;
		_memset(old_nick, 0x0, MAX_NICK_LEN + 1);
		_memcpy(old_nick, command[1], size);
		_memset(user->nick, 0x0, MAX_NICK_LEN);
		_memcpy(user->nick, command[1], size);
		send_response(user);
		notify_channel(user, old_nick);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
