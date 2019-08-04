/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:00:32 by ddinaut           #+#    #+#             */
/*   Updated: 2019/07/29 14:37:00 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	init_fd(t_list_user *user)
{
	FD_ZERO(&user->client.read);
	FD_ZERO(&user->client.write);
	FD_SET(STDIN_FILENO, &user->client.read);
	if (user->connected == true)
	{
		FD_SET(user->socket, &user->client.read);
		FD_SET(user->socket, &user->client.write);
	}
}

static void	reset_data(t_interface *inter, char *input)
{
	_memset(input, 0x0, MAX_INPUT_LEN);
	inter->off = 0;
	inter->curmax = 0;
	inter->cursor = 3;
	wclear(inter->bot);
	refresh_bot_interface(inter, input);
}

static void	read_from_user(t_interface *inter, t_list_user *user)
{
	wint_t key;

	key = wgetch(inter->bot);
	if (key == KEY_LEFT)
		do_key_left(inter, user->input);
	else if (key == KEY_RIGHT)
		do_key_right(inter, user->input);
	else if (key == KEY_UP)
		do_key_up(inter, user->input);
	else if (key == KEY_DOWN)
		do_key_down(inter, user->input);
	else if (key == 127) // delete macro doesn't works
		delete_char(inter, user->input);
	else if (key == '\n')
	{
		interpreter(inter, user);
		reset_data(inter, user->input);
	}
	else
		insert_char(inter, user->input, key);
}

static void	read_from_server(t_interface *inter, t_list_user *user)
{
	char data[MAX_INPUT_LEN];

	_memset(&data, 0x0, sizeof(data));
	if (recv(user->socket, data, MAX_INPUT_LEN, 0) < 1)
	{
		refresh_top_interface(inter, "Disconnected from server :_: : %s", strerror(errno));
		close(user->socket);
		user->connected = false;
		return ;
	}
	refresh_top_interface(inter, "%s", data);
	refresh_bot_interface(inter, user->input);
}

void	running(t_interface *inter, t_list_user *user)
{
	while (user->running == true)
	{
		init_fd(user);

		// socket == 0 if not connected or + if connected, and 0 == stdin
		if (select(user->socket + 1, &user->client.read, &user->client.write, NULL, NULL) < 0)
			return ;

		// receive data from stdin
		if (FD_ISSET(STDIN_FILENO, &user->client.read))
			read_from_user(inter, user);

		// reveive data from server
		if (user->connected == true)
		{
			if (FD_ISSET(user->socket, &user->client.read))
				read_from_server(inter, user);
		}
	}
}