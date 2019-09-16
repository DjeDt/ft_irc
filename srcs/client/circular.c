/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/13 17:37:34 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void extract_and_update(t_circular *circ, char *final)
{
	int count;

	count = 0;
	while (count < circ->len)
	{
		if (circ->buf[circ->head] == 0xd && circ->buf[circ->head + 1] == 0xa)
		{
			circ->head = (circ->head + 1) % MAX_INPUT_LEN;
			circ->head = (circ->head + 1) % MAX_INPUT_LEN;
			circ->len = (count + 2);
			break ;
		}
		final[count] = circ->buf[circ->head];
		circ->head = (circ->head + 1) % MAX_INPUT_LEN;
		count++;
	}
	final[count] = '\0';
}

bool	search_for_crlf(char *buf, int head, int size)
{
	while (size)
	{
		if (buf[head] == 0xd && buf[head + 1] == 0xa)
			return (true);
		head = (head + 1) % MAX_INPUT_LEN;
		size--;
	}
	return (false);
}

void	circular_push(t_circular *circ, char *received, int size)
{
	while (size)
	{
		circ->buf[circ->tail] = *received++;
		circ->tail = (circ->tail + 1) % MAX_INPUT_LEN;
		size--;
	}
}

bool		circular_get(t_interface *inter, t_list_user *user)
{
	int		ret;
	char	data[MAX_INPUT_LEN + 3];

	ft_memset(data, 0x0, MAX_INPUT_LEN + 3);
	ret = recv(user->socket, data, MAX_INPUT_LEN - user->circ.len, 0);
	if (ret < 1)
	{
		refresh_top_interface(inter, "Can't receive data from server\n");
		return (false);
	}
	circular_push(&user->circ, data, ret);
	user->circ.len += ret;
	return (true);
}

void	circular_send(t_interface *inter, t_list_user *user)
{
	if (send(user->socket, user->input, inter->len, 0) < 0)
	{
		refresh_top_interface(inter, "Can't send data to server.\n");
		return ;
	}
}
