/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 14:14:27 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool	search_for_crlf(t_circular *circ, int size)
{
	int	head;

	puts("TITU");
	head = circ->head;
	puts("SDFGSDFGSDFG");
	while (size >= 0)
	{
		puts("AA");
		if (*(unsigned int*)&circ->buf[head] == CRLF_HEX)
		{
			puts("BB");
			*(unsigned int*)&circ->buf[head] = 0x0000;
			puts("CC");
			return (true);
		}
		puts("DD");
		head = (head + 1) % MAX_INPUT_LEN;
		puts("EE");
		size--;
	}
	return (false);
}

void	circular_push(t_circular *circ, char *data, int size)
{
	while (size)
	{
		circ->buf[circ->tail] = *data++;
		circ->tail = (circ->tail + 1) % MAX_INPUT_LEN;
		size--;
	}
}

bool		circular_get(int socket, t_circular *circ)
{
	int		ret;
	char	data[MAX_INPUT_LEN + 3];

	ret = recv(socket, data, MAX_INPUT_LEN - circ->len, 0);
	printf("DEBUG : ret = %d ^ recv '%s'\n", ret, data);
	if (ret < 1)
	{
		printf("[LOG !] Can't receive data from [%d]\n", socket);
		return (false);
	}
	circular_push(circ, data, ret);
	circ->len += ret;
	return (true);
}

void	circular_send(int socket, char *data, int size)
{
	if (send(socket, data, size, 0) < 0)
	{
		printf("[LOG !] Can't send data to %d\n", socket);
		return ;
	}
}
