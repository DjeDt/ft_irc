/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:43:26 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/01 11:36:30 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static bool	is_available(t_users *usr_list, t_users *user, char *nick, int size)
{
	t_users *tmp;

	tmp = usr_list;
	while (tmp != NULL)
	{
		if (user->socket != tmp->socket)
		{
			if (ft_strncmp(tmp->nick.nick, nick,  \
				size > tmp->nick.nick_len ? size : tmp->nick.nick_len) == 0)
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}

static bool	check_nick(t_users *users_list, t_users *user, char *nick, int size)
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

static void	send_response(t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, NICK_RESP, user->nick.nick);
	circular_send(user->socket, buf, len);
}

static void	notify_channel(t_users *user, char *old)
{
	int				len;
	char			buf[MAX_INPUT_LEN + CRLF];
	t_channel_user	*tmp;

	if (user->chan != NULL)
	{
		len = snprintf(buf, MAX_INPUT_LEN + CRLF, NICK_NOTIF, old, \
			user->nick.nick);
		tmp = ((t_channel*)user->chan)->users;
		while (tmp != NULL)
		{
			if (tmp->user->socket != user->socket)
				circular_send(tmp->user->socket, buf, len);
			tmp = tmp->next;
		}
	}
}

void		irc_nick(t_server *server, t_users *user, char **command)
{
	int		size;
	char	old_nick[MAX_NICK_LEN + 1];

	if (command[1] != NULL)
	{
		if (command[2] != NULL)
		{
			err_toomanyarguments(user, command[1]);
			return ;
		}
		size = ft_strlen(command[1]);
		if (check_nick(server->users, user, command[1], size) != true)
			return ;
		ft_memset(old_nick, 0x0, MAX_NICK_LEN + 1);
		ft_memcpy(old_nick, user->nick.nick, user->nick.nick_len);
		ft_memset(user->nick.nick, 0x0, MAX_NICK_LEN);
		ft_memcpy(user->nick.nick, command[1], size);
		send_response(user);
		notify_channel(user, old_nick);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
