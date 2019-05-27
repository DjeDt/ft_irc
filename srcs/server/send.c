/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 10:55:17 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/21 17:05:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool	send_data(int fd, char *data, int size, int flag)
{
	int tmp;
	int sent;

	sent = 0;
	while (sent < size)
	{
		tmp = send(fd, data + sent, size, flag);
		if (tmp <= 0)
		{
			if (tmp < 0)
				perror("send");
			return (false);
		}
		sent += tmp;
	}
	send(fd, "\n", 1, flag);
	printf("send %d data to %d socket\n", sent, fd);
	return (true);
}

#define WELCOME_SIZE 374
void	send_welcome(int off)
{
	char welcome[] =									\
		"######## ########   #### ########   ######\n"
		"##          ##       ##  ##     ## ##    ##\n"
		"##          ##       ##  ##     ## ##\n"
		"######      ##       ##  ########  ##\n"
		"##          ##       ##  ##   ##   ##\n"
		"##          ##       ##  ##    ##  ##    ##\n"
		"##          ##      #### ##     ##  ######\n\n"
		"\t******\n"
		"\tWelcome here. type '/help' to get help or '/join general' to begin!\n"
		"\t******\n";

	send_data(off, welcome, WELCOME_SIZE, 0);
}

bool	send_to_all(t_server *server, t_client *client, t_data data, int count)
{
	int curr;

	curr = 0;
	while (curr <= client->fd_max)
	{
		if (FD_ISSET(curr, &client->master))
		{
			if (curr != server->socket && curr != count)
			{
				send_data(curr, data.data, data.len, 0);
				// if == false -> log error
			}
		}
		curr++;
	}
	return (true);
}
