/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:43:26 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/29 17:04:15 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_nick(t_server *server, char **command, int off)
{
	int			len;
	t_list_user *user;

	if (command[1] != NULL)
	{
		len = _strlen(command[1]);
		if (len < 1 || len > MAX_NICK_LEN)
			return ;
		user = search_user_by_id(server->users, off);
		if (user != NULL)
		{
			_memset(user->nick, 0x0, MAX_NICK_LEN);
			_memcpy(user->nick, command[1], len);
			send_data(off, "nick set\n", 9, 0);
			printf("[+] NICK set to '%s'\n", user->nick);
		}
	}
	printf("[-] NICK failed\n");
}
