/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:10:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 16:11:06 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_list(t_server *server, t_users *user, char **command)
{
	t_data		data;
	t_channel	*tmp;

	(void)command;
	tmp = server->channel;
	rpl_liststart(user, &data);
	while (tmp != NULL)
	{
		memset(&data, 0x0, sizeof(t_data));
		rpl_list(tmp, user, &data);
		tmp = tmp->next;
	}
	rpl_endoflist(user, &data);
}
