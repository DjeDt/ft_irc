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

void test(t_server *server)
{
	char	chan_name[] = "toto";
  	char	*cmd_join[3] = {"/join", chan_name};
	char	*cmd_leav[3] = {"/leave", chan_name};

	t_users *user0, *user1;
	int		sock0 = 0, sock1 = 1;

	user_add(&server->users, sock0);
	user_add(&server->users, sock1);

	user0 = user_search_by_id(server->users, sock0);
	user1 = user_search_by_id(server->users, sock1);

	channel_add(&server->channel, "toto");
	channel_add(&server->channel, "tata");
	channel_add(&server->channel, "tutu");

	channel_delete(&server->channel, "tutu");
	channel_delete(&server->channel, "tata");
	channel_delete(&server->channel, "toto");

	irc_join(server, user0, cmd_join);
	irc_leave(server, user0, cmd_leav);

	irc_join(server, user0, cmd_join);
	irc_join(server, user1, cmd_join);

	irc_leave(server, user0, cmd_leav);
	irc_leave(server, user1, cmd_leav);

	irc_join(server, user0, cmd_join);
	irc_leave(server, user0, cmd_leav);


	int i = 0;
	t_channel *chan = server->channel;

	while (chan != NULL)
	{
		printf("FOUND chan '%s'\n", chan->name);
		chan = chan->next;
		i++;
	}
	if (i == 0)
		printf("NO CHANNEL\n");
	else
		puts("CHANNEL LIST NOT EMPPTY");

	return ;
}

int		main(int ac, char **av)
{
	t_server server;

	memset(&server, 0x0, sizeof(t_server));
//	test(&server);
//	return (0);

	if (ac == 1)
	{
		printf("No port provided, using default '%s'\n", DEFAULT_PORT);
		if (initialize(&server, DEFAULT_PORT) == true)
			if (running(&server) == true)
				return (SCS);
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
