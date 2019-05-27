/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/24 13:52:33 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	init_data(t_data *data)
{
	_memset(data, 0x0, sizeof(*data));
	data->data[MAX_INPUT_LEN] = '\n';
	data->data[MAX_INPUT_LEN - 1] = '\r';
}

int		receive_full(int off, char *data, size_t size, int flag)
{
	int	tmp;
	int	received;

	tmp = 0;
	received = 0;
	while (size > 0)
	{
		tmp = recv(off, data + received, size, flag);
		if (tmp < 1)
		{
			printf("[-] Can't read from %d socket. Closing it\n", off);
			return (-1);
		}
		received += tmp;
		size -= tmp;
		if (_strchr(data, '\n') != NULL)
			return (MAX_INPUT_LEN - size);
	}
	return (received);
}

bool	receive_data(t_server *server, t_data *data, int off)
{

	(void)server;
	(void)data;
	(void)off;
	/* init_data(data); */
	/* if (data.len > 0) */
	/* { */

	/* 	printf("received %d data from socket %d\n", data.len, off); */
	/* 	printf("\t%s\n", data.data); */

	/* 	if (data.data[0] == '/') */
	/* 		interpreter(server, data, off); */
	/* 	/\* else *\/ */
	/* 	/\* 	send_to_all(server, client, data, off); *\/ */

	/* 	return (true); */
	/* } */
	/* close(off); */
	/* FD_CLR(off, &server->client.master); */
	return (false);
}
