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

//	t_channel *chan;
	char	chan_name[] = "toto";
  	char *cmd_join[3] = {"/join", chan_name};
	char *cmd_leav[3] = {"/leave", chan_name};

	/* channel_add(&server.channel, chan_name); */
	/* chan = channel_search(server.channel, chan_name); */

	user_add(&server.users, 0);
//	user_add(&server.users, 1);

	irc_join(&server, cmd_join, 0);
	irc_leave(&server, cmd_leav, 0);

	irc_join(&server, cmd_join, 0);
	irc_leave(&server, cmd_leav, 0);


	t_channel *chan;

	chan = server.channel;
	int i = 0;
	//for (i = 0; chan != NULL && i++ ; chan = chan->next)
	while (chan != NULL)
	{
		printf("FOUND chan '%s'\n", chan->name);
		chan = chan->next;
		i++;
	}
	if (i == 0)
		printf("NO CHANNEL\n");


	/* user_add(&server.users, 2); */
	/* user_add(&server.users, 3); */

	/* irc_join(&server, command, 0); */
	/* irc_join(&server, command, 1); */
	/* irc_leave(&server, command2, 1); */
	/* irc_join(&server, command, 1); */

	/* irc_join(&server, command, 2); */
	/* irc_join(&server, command, 3); */

	/* irc_leave(&server, command2, 1); */
	/* irc_leave(&server, command2, 0); */
	/* irc_leave(&server, command2, 2); */
	/* irc_leave(&server, command2, 3); */

	/* if (channel_search(server.channel, "toto") == NULL) */
	/* 	puts("TOTO NULL"); */
	/* else */
	/* 	print_channel_user(chan->users); */

	return (0);
}

int		main(int ac, char **av)
{
	t_server server;

	bzero(&server, sizeof(server));
	test(server);
	return (0);

	if (ac == 1)
	{
		printf("No port porovided, using default '%s'\n", DEFAULT_PORT);
		if (initialize(&server, DEFAULT_PORT) != true)
			return (ERR);
	}
	else if (ac == 2)
	{

		if (is_valid_argument(av[1]) == true && initialize(&server, av[1]) == true)
			if (running(&server) == true)
				return (SCS);
		return (ERR);
	}
	else
	{
		error(INVALID_ARG, av[0]);
		return (ERR);
	}
	return (SCS);
}
