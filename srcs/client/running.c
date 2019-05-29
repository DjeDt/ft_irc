/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:00:32 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/29 15:37:18 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	init_fd(t_list_user *user)
{
	FD_ZERO(&user->client.read);
	FD_SET(STDIN_FILENO, &user->client.read);
	user->client.fd_max = STDIN_FILENO;
	if (user->socket)
	{
		FD_SET(user->socket, &user->client.read);
		user->client.fd_max = user->socket;
	}
}

void	reset_data(t_interface *inter, char *input)
{
	_memset(input, 0x0, MAX_INPUT_LEN);
	inter->off = 0;
	inter->curmax = 0;
	inter->cursor = 3;
	wclear(inter->bot);
	refresh_bot_interface(inter, "");
}

void	dispatch_key(t_interface *inter, char *input)
{
	int c;

	c = wgetch(inter->bot);
	if (c == KEY_LEFT)
		do_key_left(inter, input);
	else if (c == KEY_RIGHT)
		do_key_right(inter, input);
	else if (c == KEY_UP)
		do_key_up(inter, input);
	else if (c == KEY_DOWN)
		do_key_down(inter, input);
	else
		insert_char(inter, input, c);
}

void	processing(t_interface *inter, t_list_user *user)
{
	int		off;
	t_data	data;

	off = 0;
	while (off <= user->client.fd_max)
	{
		if (FD_ISSET(off, &user->client.read))
		{
			if (off == STDIN_FILENO)
				dispatch_key(inter, user->input);
			else
			{
				// received data from server
				_memset(&data, 0x0, sizeof(data));
				receive_data(off, &data, MAX_INPUT_LEN, 0);
				refresh_top_interface(inter, data.data);
				refresh_bot_interface(inter, user->input);
			}
		}
		off++;
	}
}

void	running(t_interface *inter, t_list_user *user)
{
	init_fd(user);
	while (true)
	{
		if (select(user->client.fd_max + 1, &user->client.read, &user->client.write, NULL, NULL) < 0)
			return ;
		processing(inter, user);
		if (_strchr(user->input, '\n'))
		{
			interpreter(inter, user);
			reset_data(inter, user->input);
		}
	}
}
