/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:31:12 by ddinaut           #+#    #+#             */
/*   Updated: 2019/07/29 15:54:07 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	init_data(t_interface *inter, t_list_user *user)
{
	_memset(inter, 0x0, sizeof(*inter));
	_memset(user, 0x0, sizeof(*user));
	user->running = true;
	user->connected = false;
	if (init_interface(inter) != true)
		return (false);
	return (true);
}

int		main(int ac, char **av)
{
	t_list_user	user;
	t_interface	inter;

	if (init_data(&inter, &user) != true)
	{
		printf("Can't initialize interface, abort.");
		return (-1);

	}
	if (ac == 2)
		irc_connect(&inter, &user, av[1], DEFAULT_PORT);
	else if (ac == 3)
		irc_connect(&inter, &user, av[1], av[2]);
	else
		refresh_top_interface(&inter, "Use '/connect [ip] [port]'", av[0]);
	running(&inter, &user);
	endwin();
	return (0);
}
