/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_whoreply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:59:17 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/18 13:26:26 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_whoreply(t_channel *chan, t_users *user, char *nick, char *buf)
{
	int len;

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, RPL_WHOREPLY, chan->name, nick);
	circular_send(user->socket, buf, len);
}
