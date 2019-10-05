/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:31:12 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/04 20:16:03 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	init_data(t_interface *inter, t_user *user)
{
	ft_memset(inter, 0x0, sizeof(t_interface));
	ft_memset(user, 0x0, sizeof(t_user));
	ft_memset(&user->read, 0x0, sizeof(t_circular));
	user->running = true;
	user->connected = false;
	inter->status = false;
	init_interface(inter);
	if (inter->status == false)
		printf("Can't use ncurse. Using basic client instead\n");
}

int			main(int ac, char **av)
{
	bool		ret;
	t_user		user;
	t_interface	inter;

	ret = true;
	init_data(&inter, &user);
	if (ac == 2)
		ret = irc_connect(&inter, &user, av[1], DEFAULT_PORT);
	else if (ac == 3)
		ret = irc_connect(&inter, &user, av[1], av[2]);
	else
		refresh_top_interface(&inter, "Usage: %s [ip] [port]'", av[0]);
	if (ret == false)
		refresh_top_interface(&inter, "Can't connect to %s:%s.", av[1], av[2]);
	running(&inter, &user);
	endwin();
	return (SUCCESS);
}
