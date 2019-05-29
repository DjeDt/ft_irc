/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:24:36 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/28 15:26:06 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool    receive_data(int off, t_data *data, size_t size, int flag)
{
	int tmp;

	tmp = 0;
	while (size > 0)
	{
		tmp = recv(off, data->data + data->len, size, flag);
		// if 0 : user closed the connection
		// if -1: recv error
		if (tmp < 1)
			return (false);
		data->len += tmp;
		size -= tmp;
		if (_strchr(data->data, '\n') != NULL)
			break ;
	}
	return (true);
}
