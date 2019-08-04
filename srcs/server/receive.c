/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 19:12:46 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool	receive_data(int off, t_data *data, size_t size, int flag)
{

	if ((data->len = recv(off, data->data, size, flag)) < 1)
	{
		perror("recv");
		return (false);
	}
	printf("received %d octets from %d -> [%s]\n", data->len, off, data->data);
	return (true);
}
