/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:46:44 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 21:46:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	gather_all_user_in_chan(t_channel *chan, t_users *user)
{
	char			buf[MAX_INPUT_LEN + 3];
	t_channel_user	*tmp;

	tmp = chan->users;
	while (tmp != NULL)
	{
		rpl_whoreply(chan, user, tmp->user->nick.nick, buf);
		tmp = tmp->next;
	}
	rpl_endofwho(chan, user, buf);
}

void		irc_who(t_server *server, t_users *user, char **command)
{
	t_channel	*chan;

	if (command[1] != NULL)
	{
		chan = channel_search(&server->channel, command[1]);
		if (chan == NULL)
		{
			err_nosuchchannel(user, command[1]);
			return ;
		}
		gather_all_user_in_chan(chan, user);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
