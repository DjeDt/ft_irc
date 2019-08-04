/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 09:55:48 by ddinaut           #+#    #+#             */
/*   Updated: 2019/06/13 10:25:39 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	irc_nick(t_interface *inter, t_list_user *user, char **command)
{
	if (user->connected == true)
	{
		if (command[1] != NULL)
		{
			if (_strlen(command[1]) < MAX_NICK_LEN)
			{
				if (send_data(inter, user) == true)
				{
					_memcpy(user->nick, command[1], MAX_NICK_LEN);
					return (true);
				}
			}
		}
	}
	else
		refresh_top_interface(inter, "you are not connected. use '/connect'");
	return (false);
}
