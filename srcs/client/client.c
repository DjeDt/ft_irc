/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:31:12 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/22 15:43:23 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	init_data(t_interface *inter, t_list_user *user)
{
	ft_memset(inter, 0x0, sizeof(t_interface));
	ft_memset(user, 0x0, sizeof(t_list_user));
	ft_memset(&user->circ, 0x0, sizeof(t_circular));
	user->running = true;
	user->connected = false;
	inter->status = false;
	init_interface(inter);
	if (inter->status == false)
		printf("Can't use ncurse. Using basic client instead\n");
	return (true);
}

int		main(int ac, char **av)
{
	t_list_user	user;
	t_interface	inter;

	if (init_data(&inter, &user) != true)
	{
		puts("Can't initialize interface, abort.");
		return (ERROR);
	}
	if (ac == 2)
		irc_connect(&inter, &user, av[1], DEFAULT_PORT);
	else if (ac == 3)
		irc_connect(&inter, &user, av[1], av[2]);
	else
		refresh_top_interface(&inter, "Use '/connect [ip] [port]'", av[0]);
	running(&inter, &user);
	endwin();
	return (SUCCESS);
}
