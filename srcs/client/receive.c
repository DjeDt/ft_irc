/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 11:09:10 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/24 11:32:08 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	receive_full(int off, t_data *data, size_t size, int flag)
{
	int	tmp;

	tmp = 0;
	while (size > 0)
	{
		tmp = recv(off, data->data + data->len, size, flag);
		if (tmp < 0)
		{
			printf("[-] Can't read from %d socket. Closing it\n", off);
			return (false);
		}
		size -= tmp;
		data->len += tmp;
		if (_strchr(data->data, '\n') != NULL)
		{
			data->len = _strlen(data->data);
			return (true);
		}
	}
	return (true);
}

bool	receive_data(t_users *user, int off)
{
	t_data data;

	_memset(&data, 0x0, sizeof(data));
	if (receive_full(off, &data, MAX_INPUT_LEN, 0) == true)
	{
		if (data.data[0] == '/')
			interpreter(user, data);
		else
			printf("%s", data.data);
		return (true);
	}
	close(off);
	FD_CLR(off, &user->client.master);
	return (false);
}
