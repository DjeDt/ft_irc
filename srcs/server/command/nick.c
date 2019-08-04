/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:43:26 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 16:30:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_response(char *nick, int off)
{
	t_data data;

	data.len = snprintf(data.data, MAX_INPUT_LEN, "nickname set to : '%s'.\n", nick);
	send_data_to_single(off, data.data, data.len);
}

void	irc_nick(t_server *server, char **command, int off)
{
	int		len;
	t_users	*user;

	if (command[1] != NULL)
	{
		len = _strlen(command[1]);
		if (len < 1 || len > MAX_NICK_LEN)
			return ;
		user = user_search_by_id(server->users, off);
		if (user != NULL)
		{
			_memset(user->nick, 0x0, MAX_NICK_LEN);
			_memcpy(user->nick, command[1], len);
			send_response(user->nick, off);
		}
		else
			send_data_to_single(off, "this nickname is already taken.\n", 32);
	}
	printf("[-] NICK failed\n");
}
