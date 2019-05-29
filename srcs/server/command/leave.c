/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:41:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/29 18:13:45 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_leave(t_server *server, char **command, int off)
{
	t_data		data;
	t_channel	*chan;

	if (command[1] != NULL)
	{
		chan = search_channel(server->chan, command[1]);
		if (chan == NULL)
			data.len = snprintf(data.data, MAX_INPUT_LEN, "channel '%s' doesn't exist.", command[1]);
		else if (FD_ISSET(off, &chan->connected))
		{
			chan->num -= 1;
			FD_CLR(off, &chan->connected);
			if (chan->num == 0)
				delete_channel(&server->chan, chan->name);
			data.len = snprintf(data.data, MAX_INPUT_LEN, "Disconnected from '%s'.", command[1]);
		}
		else
			data.len = snprintf(data.data, MAX_INPUT_LEN, "You aren't connected to '%s'.", command[1]);
		send_data(off, data.data, data.len, 0);
	}
}
