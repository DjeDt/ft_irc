/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:10:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/18 13:35:37 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_list(t_server *server, t_users *user, char **command)
{
	char		buf[MAX_INPUT_LEN + CRLF];
	t_channel	*tmp;

	(void)command;
	tmp = server->channel;
	rpl_liststart(user, buf);
	while (tmp != NULL)
	{
		rpl_list(tmp, user, buf);
		tmp = tmp->next;
	}
	rpl_endoflist(user, buf);
}
