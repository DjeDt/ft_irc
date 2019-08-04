/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:46:44 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/02 14:09:03 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_who(t_server *server, char **command, int off)
{
	int		count;
	t_data	data;
	t_users *user;

	if (command[0] != NULL)
	{
		count = 0;
		if (server->users != NULL)
		{
			user = server->users;
			while (user != NULL)
			{
				if (off != user->socket)
				{
					count++;
					send_data_to_single(off, user->nick, _strlen(user->nick));
				}
				user = user->next;
			}
		}
		if (count < 1)
		{
			data.len = snprintf(data.data, MAX_INPUT_LEN, "there is no user connected :(.\n");
			send_data_to_single(off, data.data, data.len);
		}
	}
}
