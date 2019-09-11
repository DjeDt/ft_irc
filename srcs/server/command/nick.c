/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:43:26 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 16:56:15 by ddinaut          ###   ########.fr       */
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
			if (strncmp(tmp->nick.nick, nick, size > tmp->nick.nick_len ? size : tmp->nick.nick_len) == 0)
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
	int		len;
	char	buf[MAX_INPUT_LEN + 3] = {0};

	len = snprintf(buf, MAX_INPUT_LEN + 3, "You are now known as '%s'.%s", user->nick.nick, CRLF);
	circular_send(user->socket, buf, len);
}

void	notify_channel(t_users *user, char *old_nick)
{
	int				len;
	char			buf[MAX_INPUT_LEN + 3] = {0};
	t_channel_user	*tmp;

	if (user->chan != NULL)
	{
		len = snprintf(buf, MAX_INPUT_LEN + 3, "'%s' is now known as '%s'.%s", old_nick, user->nick.nick, CRLF);
		tmp = ((t_channel*)user->chan)->users;
		while (tmp != NULL)
		{
			if (tmp->user->socket != user->socket)
				circular_send(user->socket, buf, len);
			tmp = tmp->next;
		}
	}
}

void	irc_nick(t_server *server, t_users *user, char **command)
{
	int		size;
	char	old_nick[MAX_NICK_LEN + 1] = {0};

	if (command[1] != NULL)
	{
		size = _strlen(command[1]);
		if (check_nick(server->users, user, command[1], size) != true)
			return ;
		_memset(old_nick, 0x0, MAX_NICK_LEN + 1);
		_memcpy(old_nick, command[1], size);
		_memset(user->nick.nick, 0x0, MAX_NICK_LEN);
		_memcpy(user->nick.nick, command[1], size);
		send_response(user);
		notify_channel(user, old_nick);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
