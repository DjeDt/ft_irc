/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:08:40 by ddinaut           #+#    #+#             */
/*   Updated: 2019/07/29 15:12:34 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	irc_who(t_interface *inter, t_list_user *user, char **command)
{
	(void)command;
	if (user->connected == true)
		send_data(inter, user);
	else
		refresh_top_interface(inter, "you are not connected. use '/connect'");
}