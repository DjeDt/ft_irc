/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:10:56 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 23:15:55 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	send_data(t_interface *inter, t_list_user *user)
{
	if (inter->curmax > 0)
	{
		if (FD_ISSET(user->socket, &user->client.write))
		{
			user->data.type = MESSAGE_CODE;
			user->data.err = false;
			strncat(user->data.data, CRLF, CRLF_LEN);
			if (send(user->socket, &user->data, sizeof(t_data), 0) < 0)
				refresh_top_interface(inter, "[error] Can't send data to server\n");
			else
				return (true);
		}
	}
	return (false);
}
