/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 10:55:17 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 23:29:40 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"


// TODO CIRVULAR BUFFER
bool	send_data_to_single_user(int socket, t_data *data)
{
	if (send(socket, data, sizeof(t_data), 0) < 1)
	{
		perror("send");
		return (false);
	}
	return (true);
}
