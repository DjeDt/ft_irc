/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:20:59 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 20:50:44 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static bool	is_valid_argument(const char *str)
{
	int count;

	count = 0;
	while (str[count] != '\0')
	{
		if (str[count] < '0' || str[count] > '9')
		{
			error(INVALID_ARG, str);
			return (false);
		}
		count++;
	}
	return (true);
}

static bool	launcher(t_server *server, char *port)
{
	if (is_valid_argument(port) != true || initialize(server, port) != true)
		return (false);

	if (running(server) != true)
		return (false);

	return (true);
}

int			main(int ac, char **av)
{
	t_server server;

	memset(&server, 0x0, sizeof(t_server));
	if (ac == 1)
	{
		printf("[LOG !] No port provided, using default '%s'\n", DEFAULT_PORT);
		if (launcher(&server, DEFAULT_PORT) != true)
			return (ERROR);
	}
	else if (ac == 2)
	{
		if (launcher(&server, av[1]) != true)
			return (ERROR);
	}
	else
	{
		error(INVALID_ARG, av[0]);
		return (ERROR);
	}
	return (ERROR);
}
