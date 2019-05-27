/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:52:51 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/24 11:34:15 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	init_fd(t_users *user)
{
	FD_ZERO(&user->client.master);
	FD_SET(STDIN_FILENO, &user->client.master);
	FD_SET(user->socket, &user->client.master);
	user->client.fd_max = user->socket;
}

void	processing(t_users *user)
{
	int		off;
	t_data	data;

	off = 0;
	while (off <= user->client.fd_max)
	{
		if (FD_ISSET(off, &user->client.master))
		{
			_memset(&data, 0x0, sizeof(data));
			if (off == user->socket)
			{
				// received data from server
				receive_full(off, &data, MAX_INPUT_LEN, 0);
				printf("%s", data.data);
			}
			else
			{
				read(0, data.data, MAX_INPUT_LEN);
				//				receive_data(user, off);
				/* if (data.data[0] == '/') */
				/* 	interpreter(user, data); */
				/* else */
				/* 	printf("%s", data.data); */
//				receive_data(user, off);
				/* // then input from stdin received */
			}
		}
		off++;
	}
}

void	running(t_users *user)
{
	init_fd(user);
	while (true)
	{
		if (select(user->client.fd_max + 1, &user->client.master, NULL, NULL, NULL) < 0)
		{
			perror("select");
			return ;
		}
		processing(user);
	}
}
