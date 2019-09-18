/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:35:50 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/18 13:33:42 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	setup_message_to_user(t_users *src, t_users *dst, const char *msg)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, MESSAGE_STR, src->nick.nick, msg);
	circular_send(dst->socket, buf, len);
}

static void	setup_message_to_chan(t_users *src, t_channel *dst, const char *msg)
{
	int				len;
	char			buf[MAX_INPUT_LEN + CRLF];
	t_channel_user	*tmp;

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, MESSAGE_STR, src->nick.nick, msg);
	tmp = dst->users;
	while (tmp != NULL)
	{
		circular_send(tmp->user->socket, buf, len);
		tmp = tmp->next;
	}
}

void		irc_msg(t_server *server, t_users *user, char **command)
{
	void	*dst;
	t_users	*src;

	if (command[1] != NULL && command[2] != NULL)
	{
		src = user_search_by_id(server->users, user->socket);
		if (!src)
			return ;
		dst = user_search_by_name(server->users, command[1]);
		if (dst != NULL)
		{
			setup_message_to_user(src, (t_users*)dst, command[2]);
			return ;
		}
		dst = channel_search(&server->channel, command[1]);
		if (dst != NULL)
		{
			setup_message_to_chan(src, (t_channel*)dst, command[2]);
			return ;
		}
		err_nosuchnick(user, command[1]);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
