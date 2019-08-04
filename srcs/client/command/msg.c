/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 12:58:57 by ddinaut           #+#    #+#             */
/*   Updated: 2019/06/13 10:16:59 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	irc_msg(t_interface *inter, t_list_user *user, char **command)
{
	if (user->connected == true)
	{
		if (command[1] != NULL && command[2] != NULL)
			send_data(inter, user);
		else
			refresh_top_interface(inter, "error: /message [user/chan] [msg]");
	}
	else
		refresh_top_interface(inter, "you are not connected. use '/connect'");
}
