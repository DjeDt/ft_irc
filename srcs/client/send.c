/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:10:56 by ddinaut           #+#    #+#             */
/*   Updated: 2019/07/31 14:09:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	send_data(t_interface *inter, t_list_user *user)
{
	int	len;

	if (_strlen(user->data.data) > 0 && inter->curmax > 0)
	{
		if (FD_ISSET(user->socket, &user->client.write))
		{
			user->data.type = MESSAGE_CODE;
			len = sizeof(t_data);
			if (send(user->socket, (void*)&user->data, len, 0) < 0)
				refresh_top_interface(inter, "error send : %s", strerror(errno));
			else
				return (true);
		}
	}
	return (false);
}
