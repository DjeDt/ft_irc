/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:16 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/31 09:04:17 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_quit(t_server *server, char **command, int off)
{
	if (server->users != NULL)
	{
		remove_user(&server->users, off);
		send_data(off, "Disconnected from server.\n", 26, 0);
		close(off);
		FD_CLR(off, &server->client.master);
	}
	printf("[%s] QUIT\n", command[0]);
}
