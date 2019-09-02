/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 10:55:17 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 16:21:02 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool	send_data_to_single(int fd, char *data, size_t size)
{
	if (send(fd, data, size, 0) < 1)
	{
//		perror("send");
		return (false);
	}
	/* else */
	/* 	printf("send %ld to %d\n", _strlen(data), fd); */
	return (true);
}

bool	send_data_to_spec_chan(t_channel *chan, t_data data, char *nick)
{
	t_channel_user *tmp;

	if (chan != NULL && nick != NULL)
	{
		tmp = chan->users;
		data.len = snprintf(data.data, MAX_INPUT_LEN, "'%s' leaved channel.\n", nick);
		while (tmp != NULL)
		{
			send_data_to_single(tmp->user->socket, data.data, data.len);
			tmp = tmp->next;
		}
		return (true);
	}
	return (false);
}

bool	send_data_to_channel(t_channel *chan, t_data data, char *name, char *nick)
{
	t_data		new;
	t_channel	*tmp_chan;
	t_channel_user	*tmp_chan_usr;

	tmp_chan = channel_search(&chan, name);
	if (tmp_chan != NULL)
	{
		tmp_chan_usr = tmp_chan->users;
		new.len = snprintf(new.data, MAX_INPUT_LEN, "[%s]: <%s> %s", name, nick, data.data);
		while (tmp_chan_usr != NULL)
		{
			printf("send '%s' to '%s' channel\n", data.data, tmp_chan_usr->user->nick);
			if (tmp_chan_usr->user != NULL)
				send_data_to_single(tmp_chan_usr->user->socket, new.data, new.len);
			tmp_chan_usr = tmp_chan_usr->next;
		}
		return (true);
	}
	return (false);
}
