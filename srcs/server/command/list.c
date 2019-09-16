/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:10:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 16:11:06 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_list(t_server *server, t_users *user, char **command)
{
	char		buf[MAX_INPUT_LEN + 3];
	t_channel	*tmp;

	(void)command;
	tmp = server->channel;
	ft_memset(buf, 0x0, MAX_INPUT_LEN + 3);
	rpl_liststart(user, buf);
	while (tmp != NULL)
	{
		ft_memset(buf, 0x0, MAX_INPUT_LEN + 3);
		rpl_list(tmp, user, buf);
		tmp = tmp->next;
	}
	ft_memset(buf, 0x0, MAX_INPUT_LEN + 3);
	rpl_endoflist(user, buf);
}
