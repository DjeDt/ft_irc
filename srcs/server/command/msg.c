/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:35:50 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 16:30:42 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	setup_message(t_users *src, t_users *dst, const char *message)
{
	t_data data;

	memset(&data, 0x0, sizeof(t_data));
	data.len = snprintf(data.data, MAX_INPUT_LEN, "[msg] [%s] : %s\n", src->nick, message);
	send_data_to_single(dst->socket, data.data, data.len);
}

void	irc_msg(t_server *server, t_users *user, char **command)
{
	t_users *src;
	t_users *dst;

	if (command[1] != NULL && command[2] != NULL)
	{
		src = user_search_by_id(server->users, user->socket);
		if (!src)
			return ;
		dst = user_search_by_name(server->users, command[1]);
		if (dst)
			setup_message(src, dst, command[2]);//			send_data_to_single(dst->socket, command[2], _strlen(command[2]));
		else
			send_data_to_single(user->socket, "user not found", 15);
	}
}
