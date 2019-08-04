/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:49:31 by ddinaut           #+#    #+#             */
/*   Updated: 2019/06/13 10:16:55 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	irc_leave(t_interface *inter, t_list_user *user, char **command)
{
	if (user->connected == true)
	{
		if (command[1] != NULL)
			send_data(inter, user);
		else
			refresh_top_interface(inter, "error: /leave [channel]");
	}
	else
		refresh_top_interface(inter, "you are not connected. use '/connect'");
}
