/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/12 14:21:31 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	extract_from_circular(char *final, t_circular *circ)
{
	int count;
	int head;

	count = 0;
	head = circ->head;
	while (count < circ->len)
	{
		final[count] = circ->buf[head];
		head = (head + 1) % MAX_INPUT_LEN;
		count++;
	}
	final[count] = '\0';
}

bool	search_for_crlf(t_circular *circ, int size)
{
	int	head;

	head = circ->head;
	while (size)
	{
		if (*(unsigned int*)&circ->buf[head] == CRLF_HEX)
		{
			*(unsigned int*)&circ->buf[head] = 0x0000;
			return (true);
		}
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
