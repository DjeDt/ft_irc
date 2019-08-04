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
	if (user->input != NULL && inter->curmax > 0)
	{
		// debug
//		refresh_top_interface(inter, "send : %s", user->input);

		if (FD_ISSET(user->socket, &user->client.write))
		{
			if (send(user->socket, user->input, inter->curmax, 0) < 0)
				refresh_top_interface(inter, "error send : %s", strerror(errno));
			else
				return (true);
		}
	}
	return (false);
}
