/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/13 17:28:48 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool    search_for_crlf(char *buf, int head, int size)
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

bool	circular_get(t_users *user)
{
	int		ret;

	ret = recv(user->socket, user->circ.received, MAX_INPUT_LEN - user->circ.len, 0);
	if (ret < 1)
	{
		printf("[LOG !] Can't receive data from [%d]\n", user->socket);
		return (false);
	}
	printf("[LOG !] from %d : '%s'\n", user->socket, user->circ.received);
	circular_push(&user->circ, user->circ.received, ret);
	memset(user->circ.received, 0x0, ret);
	user->circ.len += ret;
	return (true);
}

void	circular_send(int socket, char *data, int size)
{
	if (send(socket, data, size, 0) < 0)
	{
		printf("[LOG !] Can't send data to %d\n", socket);
		return ;
	}
	else
		printf("Sent to %d len = %d|%ld : '%s'", socket, size, _strlen(data), data);
}
