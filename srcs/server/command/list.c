/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:10:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/29 17:17:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_list(t_server *server, char **command, int off)
{
	t_channel	*tmp;
	t_data		data;

	(void)command;
	if (server->chan != NULL)
	{
		tmp = server->chan;
		while (tmp != NULL)
		{
			data.len = snprintf(data.data, MAX_INPUT_LEN, "'%s': %d users connected.", tmp->name, tmp->num);
			send_data(off, data.data, data.len, 0);
			tmp = tmp->next;
		}
	}
	else
	{
		data.len = snprintf(data.data, MAX_INPUT_LEN, "There isn't any channel.");
		send_data(off, data.data, data.len, 0);
	}
}
