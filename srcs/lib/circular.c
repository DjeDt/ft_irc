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
//			*(unsigned int*)&circ->buf[head] = 0x0000;
			return (true);
		}
		head = (head + 1) % MAX_INPUT_LEN;
		size--;
	}
	return (false);
}

void	circular_push(t_circular *circ, char *received, int size)
{
	int count;

	count = 0;
	while (size)
	{
		circ->buf[circ->tail] = received[count];
		circ->tail = (circ->tail + 1) % MAX_INPUT_LEN;
		size--;
		count++;
	}
}

bool is_message_valid(const char *buf, int head, int length, const int limit)
{
	while (length)
	{
		if (*(unsigned int*)&buf[head] == CRLF_HEX)
			return (true);
		head = (head + 1) % limit;
		length -= 1;
	}

	return false;
}

void fill_buffer(char *dst, const char *src, int tail, int length, const int limit)
{
	while (length)
	{
		dst[tail] = *src++;

		tail = (tail + 1) % limit;
		length -= 1;
	}
}

bool		circular_get(int socket, t_circular *circ)
{
	int		ret;
	char	data[MAX_INPUT_LEN + 3];

	ret = recv(socket, data, MAX_INPUT_LEN - circ->len, 0);
	if (ret < 1)
	{
		printf("[LOG !] Can't receive data from [%d]\n", socket);
		return (false);
	}
	fill_buffer(circ->buf, data, circ->tail, ret, MAX_INPUT_LEN);
	circ->tail = (circ->tail + ret) % MAX_INPUT_LEN;
	circ->len += ret;

//	circular_push(circ, data, ret);

	// does bullshit
//	circ->tail = (circ->tail + ret) % MAX_INPUT_LEN;/
//	circ->len += ret;
	return (true);
}

void	circular_send(int socket, char *data, int size)
{
	if (send(socket, data, size + CRLF_LEN, 0) < 0)
	{
		printf("[LOG !] Can't send data to %d\n", socket);
		return ;
	}
}
