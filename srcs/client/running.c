/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:00:32 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/13 17:54:37 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	init_fd(t_list_user *user)
{
	FD_ZERO(&user->client.read);
	FD_ZERO(&user->client.write);
	FD_ZERO(&user->client.master);
	FD_SET(STDIN_FILENO, &user->client.master);
	user->client.fd_max = STDIN_FILENO;
	/* if (user->connected == true) */
	/* { */
	/* 	FD_SET(user->socket, &user->client.read); */
	/* 	FD_SET(user->socket, &user->client.write); */
	/* } */
}

static void	reset_data(t_interface *inter, char *buf)
{
	_memset(buf, 0x0, MAX_INPUT_LEN + 3);
	inter->off = 0;
	inter->curmax = 0;
	inter->cursor = 3;
	wclear(inter->bot);
	refresh_bot_interface(inter, buf);
}

static void	read_from_user(t_interface *inter, t_list_user *user)
{
	wint_t key;

	if (inter->status == true)
		key = wgetch(inter->bot);
	else
		key = getc(stdin);
	if (key == KEY_LEFT)
		do_key_left(inter, user->input);
	else if (key == KEY_RIGHT)
		do_key_right(inter, user->input);
	else if (key == KEY_UP)
		do_key_up(inter, user->input);
	else if (key == KEY_DOWN)
		do_key_down(inter, user->input);
	else if (key == 127)
		delete_char(inter, user->input);
	else if (key == '\n')
	{
		if (_strlen(user->input) > 0)
		{
			strcat(user->input, "\r\n");
			circular_send(inter, user);
			reset_data(inter, user->input);
		}
	}
	else
		insert_char(inter, user->input, key);
}

static void	read_from_server(t_interface *inter, t_list_user *user)
{
	char buf[MAX_INPUT_LEN + 3];

	if (circular_get(inter, user) != true)
	{
		close(user->socket);
		user->connected = false;
		refresh_top_interface(inter, "Disconnected from server :_:\n");
		return ;
	}
	while (search_for_crlf(user->circ.buf, user->circ.head, user->circ.len) == true)
	{
		extract_and_update(&user->circ, buf);
		refresh_top_interface(inter, "%s", buf);
	}

}

void	running(t_interface *inter, t_list_user *user)
{
	init_fd(user);
	while (user->running == true)
	{
		user->client.read = user->client.master;
		user->client.master = user->client.master;
		if (user->connected == true && user->socket != user->client.fd_max)
			FD_SET(user->socket, &user->client.master);
		if (select(user->socket + 1, &user->client.read, &user->client.write, NULL, NULL) < 0)
			return ;
		if (FD_ISSET(STDIN_FILENO, &user->client.read))
			read_from_user(inter, user);
		if (user->connected == true)
		{
			if (FD_ISSET(user->socket, &user->client.read))
				read_from_server(inter, user);
		}
	}
}
