/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:10:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/01 16:11:21 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	irc_list_one(t_server *server, t_users *user, char *name)
{
	int			len;
	int			cmp_len;
	t_channel	*tmp;
	char		buf[MAX_INPUT_LEN + CRLF];

	len = ft_strlen(name);
	tmp = server->channel;
	rpl_liststart(user, buf);
	while (tmp != NULL)
	{
		cmp_len = len > tmp->name_len ? len : tmp->name_len;
		if (ft_strncmp(tmp->name, name, cmp_len) == 0)
		{
			rpl_list(tmp, user, buf);
			rpl_endoflist(user, buf);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	irc_list_all(t_server *server, t_users *user)
{
	t_channel	*tmp;
	char		buf[MAX_INPUT_LEN + CRLF];

	tmp = server->channel;
	rpl_liststart(user, buf);
	while (tmp != NULL)
	{
		rpl_list(tmp, user, buf);
		tmp = tmp->next;
	}
	rpl_endoflist(user, buf);
}

void		irc_list(t_server *server, t_users *user, char **command)
{
	if (command[1] != NULL)
	{
		if (command[2] != NULL)
		{
			err_toomanyarguments(user, command[0]);
			return ;
		}
		irc_list_one(server, user, command[1]);
		return ;
	}
	irc_list_all(server, user);
}
