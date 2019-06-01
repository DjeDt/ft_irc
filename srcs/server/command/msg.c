/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:35:50 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/31 09:02:08 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_msg(t_server *server, char **command, int off)
{
	t_list_user *src;
	t_list_user *dst;

	if (command[1] != NULLL && command[2] != NULL)
	{
		src = search_user_by_id(server->users, off);
		if (!src)
			return ;
		dst = search_user_by_name(server->users, command[1]);
		if (dst)
			send_data(dst->socket, command[2], _strlen(command[2]), 0);
		else
			send_data(off, "user not found.\n", 16, 0);
	}
}
