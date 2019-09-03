/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:35:50 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:04:39 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	setup_message_to_user(t_users *src, t_users *dst, const char *message)
{
	t_data data;

	data.type = MESSAGE_CODE;
	data.err = false;
	data.len = snprintf(data.data, MAX_INPUT_LEN, "[msg] [%s] : %s\n", src->nick, message);
	send_data_to_single_user(dst->socket, &data);
}

static void	setup_message_to_channel(t_users *src, t_channel *dst, const char *message)
{
	t_data			data;
	t_channel_user	*tmp;

	data.type = MESSAGE_CODE;
	data.err = false;
	data.len = snprintf(data.data, MAX_INPUT_LEN, "[msg] [%s] : %s\n", src->nick, message);
	tmp = dst->users;
	while (tmp != NULL)
	{
		send_data_to_single_user(tmp->user->socket, &data);
		tmp = tmp->next;
	}
}

void	irc_msg(t_server *server, t_users *user, char **command)
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
			setup_message_to_channel(src, (t_channel*)dst, command[2]);
			return ;
		}
		err_nosuchnick(user, command[1]);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
