/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:20:59 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 19:11:42 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	zeroed(t_server *server)
{
	server->port = 0;
	server->sock = 0;
	memset(&server->info, 0x0, sizeof(t_fd));
	server->users = NULL;
	server->channel = NULL;
}

static bool	is_valid_argument(const char *str)
{
	int count;

	count = 0;
	while (str[count] != '\0')
	{
		if (str[count] < '0' || str[count] > '9')
		{
			printf("Error: '%s' port is invalid. Abort\n", str);
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

	zeroed(&server);
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
		printf("Usage: %s <port>\n", av[0]);
		return (ERROR);
	}
	return (ERROR);
}
