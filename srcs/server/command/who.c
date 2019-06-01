/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:46:44 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/31 09:01:10 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_who(t_server *server, char **command, int off)
{
	int			count;
	t_data		data;
	t_list_user *user;

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
					send_data(off, user->nick, _strlen(user->nick), 0);
				}
				user = user->next;
			}
		}
		if (count < 1)
		{
			data.len = snprintf(data.data, MAX_INPUT_LEN, "there is no user connected :(.");
			send_data(off, data.data, data.len, 0);
		}
	}
}
