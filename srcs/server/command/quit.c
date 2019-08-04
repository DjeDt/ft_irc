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

void	irc_quit(t_server *server, char **command, int off)
{
	t_users *users;

	if (server->users != NULL)
	{
		users = user_search_by_id(server->users, off);
		if (users != NULL)
		{
			channel_user_remove_full(server->channel, users);
			user_remove(&server->users, off);
			send_data_to_single(off, "Disconnected from server.\n", 26);
			close(off);
			FD_CLR(off, &server->info.master);
		}
	}
	printf("[%s] QUIT\n", command[0]);
}
