/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/21 17:12:26 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool	receive_data(int off, t_data *data, size_t size, int flag)
{
	int tmp;

	tmp = 0;
	while (size > 0)
	{
		tmp = recv(off, data->data + data->len, size, flag);
		// if 0 : user closed the connection
		// if -1: recv error
		if (tmp < 1)
		{
			printf("[-] Can't read from %d socket. Closing it\n", off);
			return (false);
		}
		data->len += tmp;
		size -= tmp;
		if (_strchr(data->data, '\n') != NULL)
			break ;
	}
	printf("received %d data from socket %d\n", data->len, off);
	return (true);
}
