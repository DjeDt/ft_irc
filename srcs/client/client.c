/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:08:50 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/23 19:53:08 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		main(int ac, char **av)
{
	t_users	user;

	_memset(&user, 0x0, sizeof(user));
	if (ac == 1)
		running(&user);
	else if (ac == 3)
	{
		if (connect_to_server(&user, av[1], av[2]) != true)
			return (ERR);
		running(&user);
	}
	else
	{
		error(INVALID_ARG, av[0]);
		return (ERR);
	}
	return (SCS);
}
