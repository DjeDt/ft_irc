/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:10:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/02 14:53:17 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_list(t_server *server, t_users *user, char **command)
{
	t_channel	*tmp;
	t_data		data;

	(void)command;
	if (server->channel != NULL)
	{
		tmp = server->channel;
		data.len = snprintf(data.data, MAX_INPUT_LEN, "Current channel:\n.");
		while (tmp != NULL)
		{
			data.len = snprintf(data.data, MAX_INPUT_LEN, "channel:\t'%s'.\n", tmp->name);
			send_data_to_single(user->socket, data.data, data.len);
			tmp = tmp->next;
		}
	}
	else
	{
		data.len = snprintf(data.data, MAX_INPUT_LEN, "There isn't any channel.\n");
		send_data_to_single(user->socket, data.data, data.len);
	}
}
