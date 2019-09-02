/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:16 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 16:32:20 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_quit(t_server *server, t_users *user, char **command)
{
	t_users *users;

	if (server->users != NULL)
	{
		users = user_search_by_id(server->users, user->socket);
		if (users != NULL)
		{
			channel_user_remove_full(server->channel, users);
			user_remove(&server->users, user->socket);
			send_data_to_single(user->socket, "Disconnected from server.\n", 26);
			close(user->socket);
			FD_CLR(user->socket, &server->info.master);
		}
	}
	printf("[%s] QUIT\n", command[0]);
}
