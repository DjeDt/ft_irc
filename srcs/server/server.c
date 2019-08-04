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

int test(t_server server)
{

	t_channel *chan;
  	char *command[3] = {"/join", "toto"};
	char *command2[3] = {"/leave", "toto"};

	bzero(&server, sizeof(server));
	channel_add(&server.channel, "toto");
	chan = channel_search(server.channel, "toto");

	user_add(&server.users, 0);
	user_add(&server.users, 1);
	irc_join(&server, command, 0);

	user_add(&server.users, 2);
	user_add(&server.users, 3);

	irc_join(&server, command, 0);
	irc_join(&server, command, 1);
	irc_leave(&server, command2, 1);
	irc_join(&server, command, 1);

	irc_join(&server, command, 2);
	irc_join(&server, command, 3);

	irc_leave(&server, command2, 1);
	irc_leave(&server, command2, 0);
	irc_leave(&server, command2, 2);
	irc_leave(&server, command2, 3);

	if (channel_search(server.channel, "toto") == NULL)
		puts("TOTO NULL");
	else
		print_channel_user(chan->users);

	return (0);
}

int		main(int ac, char **av)
{
	t_server server;

	/* test(server); */
	/* return (0); */

	if (ac == 1)
	{
		if (initialize(&server, DEFAULT_PORT) != true)
			return (ERR);
	}
	else if (ac == 2)
	{
		if (is_valid_argument(av[1]) != true)
			return (ERR);
		if (initialize(&server, av[1]) != true)
			return (ERR);
	}
	else
	{
		error(INVALID_ARG, av[0]);
		return (ERR);
	}

	if (running(&server) != true)
		return (ERR);
	return (SCS);
}
