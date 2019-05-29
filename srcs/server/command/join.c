/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:17:35 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/29 17:45:39 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_join(t_server *server, char **command, int off)
{
	t_data		data;
	t_channel	*chan;

	if (command[1] != NULL)
	{
		chan = search_channel(server->chan, command[1]);
		if (chan == NULL)
		{
			chan = add_channel(&server->chan, command[1]);
			chan->num += 1;
			FD_SET(off, &chan->connected);
			data.len = snprintf(data.data, MAX_INPUT_LEN, "'%s' joined.", command[1]);
		}
		else if (!FD_ISSET(off, &chan->connected))
		{
			chan->num += 1;
			FD_SET(off, &chan->connected);
			data.len = snprintf(data.data, MAX_INPUT_LEN, "'%s' joined.", command[1]);
		}
		else
			data.len = snprintf(data.data, MAX_INPUT_LEN, "Already connected to '%s'.", command[1]);
		send_data(off, data.data, data.len, 0);
	}
}
