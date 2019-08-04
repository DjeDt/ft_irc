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

void	irc_msg(t_server *server, char **command, int off)
{
	t_users *src;
	t_users *dst;

	if (command[1] != NULL && command[2] != NULL)
	{
		src = user_search_by_id(server->users, off);
		if (!src)
			return ;
		dst = user_search_by_name(server->users, command[1]);
		if (dst)
			send_data_to_single(dst->socket, command[2], _strlen(command[2]));
		else
			send_data_to_single(off, "user not found", 15);
	}
}
