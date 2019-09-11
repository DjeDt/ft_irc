/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 20:36:35 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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

bool	circular_get(t_users *user, char *received)
{
	int		ret;

	ret = recv(user->socket, received, MAX_INPUT_LEN - user->circ.len, 0);
	if (ret < 1)
	{
		printf("[LOG !] Can't receive data from [%d]\n", user->socket);
		return (false);
	}
	circular_push(&user->circ, received, ret);
	user->circ.len += ret;
	return (true);
}

void	circular_send(int socket, char *data, int size)
{
	printf("sending : '%s'", data);
	if (send(socket, data, size + CRLF_LEN, 0) < 0)
	{
		printf("[LOG !] Can't send data to %d\n", socket);
		return ;
	}
}
