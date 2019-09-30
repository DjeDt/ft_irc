/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:00:32 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/30 14:50:38 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	init_fd(t_list_user *user)
{
	FD_ZERO(&user->client.read);
	FD_ZERO(&user->client.write);
	FD_ZERO(&user->client.master);
	FD_SET(STDIN_FILENO, &user->client.master);
}

static void	reset_data(t_interface *inter, char *buf)
{
	ft_memset(buf, 0x0, MAX_INPUT_LEN + CRLF);
	inter->off = 0;
	inter->len = 0;
	inter->curmax = 0;
	inter->cursor = 3;
	wclear(inter->bot);
	refresh_bot_interface(inter, buf);
	doupdate();
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
	else if (key == 127)
		delete_char(inter, user->input);
	else if (key == '\n')
	{
		if (inter->len > 0)
		{
			inter->len += CRLF;
			interpreter(inter, user);
			reset_data(inter, user->input);
		}
	}
	else
		insert_char(inter, user->input, key);
}

static void	read_from_server(t_interface *inter, t_list_user *user)
{
	char buf[MAX_INPUT_LEN + CRLF];

	memset(buf, 0x0, MAX_INPUT_LEN + CRLF);
	if (circular_get(inter, user) != true)
	{
		FD_CLR(user->socket, &user->client.master);
		close(user->socket);
		user->connected = false;
		refresh_top_interface(inter, "Disconnected from server :_:\n");
		return ;
	}
	while (search_for_crlf(user->circ.buf, user->circ.head, user->circ.len))
	{
		extract_and_update(&user->circ, buf);
		refresh_top_interface(inter, "%s", buf);
	}
}

void		running(t_interface *inter, t_list_user *user)
{
	init_fd(user);
	while (user->running == true)
	{
		user->client.read = user->client.master;
		user->client.write = user->client.master;
		if (user->connected == true && \
			!FD_ISSET(user->socket, &user->client.master))
			FD_SET(user->socket, &user->client.master);
		if (select(user->socket + 1, &user->client.read, \
				&user->client.write, NULL, NULL) < 0)
			return ;
		if (FD_ISSET(STDIN_FILENO, &user->client.read))
			read_from_user(inter, user);
		else if (user->connected == true && \
			FD_ISSET(user->socket, &user->client.read))
			read_from_server(inter, user);
	}
}
