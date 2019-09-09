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

static bool	search_for_crlf(char *data, int size)
{
	void *ptr;

	if ((ptr = memchr(data, CRLF_HEX, size)) != NULL)
	{
		*(unsigned char*)ptr = 0x0000;
		return (true);
	}
	return (false);
}

bool	receive_data(int socket, t_data *data)
{
	int	ret;
	int	limit;
	int	offset;

	limit = sizeof(t_data);
	offset = 0;
	while (offset < limit)
	{
		ret = recv(socket, (void*)data + offset, sizeof(t_data), 0);
		if (ret < 1)
			return (false);
		if (search_for_crlf(data->data + offset, ret) == true)
			break ;
		offset += ret;
	}

	if (data->type != MESSAGE_CODE)
		return (false);

	printf("[LOG ~~] from %d -> [%s]\n", socket, data->data);
	return (true);
}
