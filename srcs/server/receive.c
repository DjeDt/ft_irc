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

bool	receive_data(int off, t_data *data)
{
	// there is only client. should be enum* MESSAGE anytimes
	if (recv(off, data, sizeof(t_data), 0) < 1)
	{
		perror("recv");
		return (false);
	}

	// drop this data if not
	if (data->type != MESSAGE_CODE)
		return (false);
	// log
	printf("[LOG ~~] %d octets from %d -> [%s]\n", data->len, off, data->data);
	return (true);
}
