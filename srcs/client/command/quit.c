/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:04:10 by ddinaut           #+#    #+#             */
/*   Updated: 2019/07/31 16:44:55 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	irc_quit(t_interface *inter, t_list_user *user, char **command)
{
	(void)command;
	if (user->connected == true)
	{
		user->running = false;
		send_data(inter, user);
	}
	else
		refresh_top_interface(inter, "you are not connected. use '/connect'");
}
