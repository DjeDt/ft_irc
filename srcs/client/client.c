/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:31:12 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/28 17:25:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	init_data(t_interface *inter, t_list_user *user)
{
	_memset(inter, 0x0, sizeof(t_interface));
	_memset(user, 0x0, sizeof(t_list_user));
}

int		main(int ac, char **av)
{
	t_list_user	user;
	t_interface	inter;

	init_data(&inter, &user);
	if (init_interface(&inter) != true)
		return (-1);
	if (ac == 1 || ac == 3)
	{
		if (ac == 3)
		{
			if (connect_to_server(&user, av[1], av[2]) != true)
				refresh_top_interface(&inter, "can't connect to given irc. use '/connect' or '/quit'.");
		}
	}
	else
		refresh_top_interface(&inter, "USAGE: ./client <ip> <port>.");
	running(&inter, &user);
	endwin();
	return (0);
}
