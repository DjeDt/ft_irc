/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:09 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/01 16:16:28 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	shutdown_users(t_users **users)
{
	int		len;
	t_users *tmp;
	t_users	*nxt;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, \
		"[server] Hello, i'm going to shut down. Bye !\r\n");
	tmp = *users;
	while (tmp != NULL)
	{
		circular_send(tmp->socket, buf, len);
		nxt = tmp->next;
		close(tmp->socket);
		free(tmp);
		tmp = nxt;
	}
}

void	shutdown_channels(t_channel **channel)
{
	t_channel	*chan;
	t_channel	*nxt;

	chan = *channel;
	while (chan != NULL)
	{
		channel_user_remove_all(&chan->users);
		nxt = chan->next;
		free(chan);
		chan = nxt;
	}
}

void	irc_kill(t_server *server, t_users *user, char **command)
{
	int len;

	if (command[1] != NULL)
	{
		if ((len = ft_strlen(command[1])) < KILL_PASS_LEN)
			len = KILL_PASS_LEN;
		if (ft_strncmp(server->kill_pass, command[1], len) == 0)
		{
			printf("[LOG :(] Valid kill command received by <%s[%d]>'.\n", \
				user->nick.nick, user->socket);
			printf("\tFreeing channels\n");
			shutdown_channels(&server->channel);
			printf("\tFreeing users\n");
			shutdown_users(&server->users);
			printf("\tFreeing command\n");
			command_free(command);
			printf("\tClosing socket\n");
			disconnectx(server->sock, SAE_ASSOCID_ANY, SAE_CONNID_ANY);
			close(server->sock);
			printf("[LOG :(] Done, Bye !\n");
			exit(EXIT_SUCCESS);
		}
	}
}
