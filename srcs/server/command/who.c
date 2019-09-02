/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:46:44 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/02 14:09:03 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	clear_buffer(t_data *data, int off)
{
	send_data_to_single(off, data->data, data->len);
	_memset(data, 0x0, sizeof(t_data));
}

static void	send_spec_list(t_channel *chan, t_users *user, t_data *data)
{
	t_channel_user *tmp;



	// TODO

	memset(data, 0x0, sizeof(t_data));
	tmp = chan->users;
	while (tmp != NULL)
	{
		tmp = tmp->next;
	}
	(void)user;
}

static void	send_full_list(t_users *users, t_data *data, int off)
{
	int		size;
	t_users	*tmp;

	tmp = users;
	memset(data, 0x0, sizeof(t_data));
	memcpy(data->data, "Connected user:\n", 15);
	data->len = 15;
	strncat(data->data, "\n", 1);
	data->len++;
	while (tmp != NULL)
	{
		size = _strlen(tmp->nick);
		if (data->len + (size + 1) >= MAX_INPUT_LEN)
			clear_buffer(data, off);
		memcpy(data->data + data->len, tmp->nick, size);
		data->len += size;
		memcpy(data->data + data->len, "\n", 1);
		data->len += 1;

//		strncat(data->data, tmp->nick, size);
//		strncat(data->data + data->len, "\n", 1);
//		data->len += (size + 1);

		tmp = tmp->next;
	}
	send_data_to_single(off, data->data, data->len);
}

void		irc_who(t_server *server, t_users *user, char **command)
{
	t_data		data;
	t_channel	*chan;

	if (command[1] != NULL)
	{
		chan = channel_search(&server->channel, command[1]);
		if (chan == NULL)
		{
			data.len = snprintf(data.data, MAX_INPUT_LEN, "channel '%s' doesn't exist.", command[1]);
			send_data_to_single(user->socket, data.data, data.len);
		}
		else
			send_spec_list(chan, user, &data);
	}
	else
		send_full_list(server->users, &data, user->socket);
}
