/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_namreply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:59:39 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/22 15:58:16 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_namreply(t_channel *chan, t_users *user, char *nick, char *buf)
{
	int	len;

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, RPL_NAMREPLY, chan->name, nick);
	circular_send(user->socket, buf, len);
}
