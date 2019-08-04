/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:39:18 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/02 10:39:19 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	check_input(char *name)
{
	int off;

	off = 0;
	while (name[off] != '\0')
		off++;
	if (off > MAX_NICK_LEN)
		return (false);
	return (true);
}

void	irc_join(t_interface *inter, t_list_user *user, char **command)
{
	if (user->connected == true)
	{
		if (command[1] != NULL)
		{
			if (check_input(command[1]) == true)
				send_data(inter, user);
		}
		else
			refresh_top_interface(inter, "error: /join [channel]");
	}
	else
		refresh_top_interface(inter, "you are not connected. use '/connect'");
}
