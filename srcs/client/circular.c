/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/18 13:56:33 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	extract_and_update(t_circular *circ, char *final)
{
	int count;
	int next;

	count = 0;
	while (count < circ->len)
	{
		next = (circ->head + 1) % MAX_INPUT_LEN;
		if (circ->buf[circ->head] == 0xd && circ->buf[next] == 0xa)
		{
			circ->head = (circ->head + 2) % MAX_INPUT_LEN;
			circ->len -= (count + 2);
			break ;
		}
		final[count] = circ->buf[circ->head];
		circ->head = next;
		count++;
	}
	final[count] = '\0';
}

bool	search_for_crlf(char *buf, int head, int size)
{
	int next;

	while (size)
	{
		next = (head + 1) % MAX_INPUT_LEN;
		if (buf[head] == 0xd && buf[next] == 0xa)
			return (true);
		head = next;
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

bool	circular_get(t_interface *inter, t_list_user *user)
{
	int		ret;
	char	data[MAX_INPUT_LEN + CRLF];

	ft_memset(data, 0x0, MAX_INPUT_LEN + CRLF);
	ret = recv(user->socket, data, (MAX_INPUT_LEN + CRLF) - user->circ.len, 0);
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
	if (send(user->socket, user->input, inter->len + 2, 0) < 0)
	{
		refresh_top_interface(inter, "Can't send data to server.\n");
		return ;
	}
}
