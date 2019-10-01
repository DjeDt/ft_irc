/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:16 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/01 10:56:45 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	notify_leave(t_channel *chan, char **command, char *nick)
{
	int				len;
	char			buf[MAX_INPUT_LEN + CRLF];
	t_channel_user	*tmp;

	if (command[1] != NULL)
		len = snprintf(buf, MAX_INPUT_LEN + CRLF, QUIT_NOTIF, nick, command[1]);
	else
		len = snprintf(buf, MAX_INPUT_LEN + CRLF, QUIT_NOTIF, nick, "quit");
	tmp = chan->users;
	while (tmp != NULL)
	{
		circular_send(tmp->user->socket, buf, len);
		tmp = tmp->next;
	}
}

void		irc_quit(t_server *server, t_users *user, char **command)
{
	t_channel	*chan;
	char		usr_nick[MAX_NICK_LEN + 1];

	chan = user->chan;
	ft_memset(usr_nick, 0x0, MAX_NICK_LEN + 1);
	ft_memcpy(usr_nick, user->nick.nick, user->nick.nick_len);
	FD_CLR(user->socket, &server->info.master);
	close(user->socket);
	if (user->chan != NULL)
		channel_user_remove_full(&server->channel, user);
	user_remove(&server->users, user->socket);
	notify_leave(chan, command, usr_nick);
}
