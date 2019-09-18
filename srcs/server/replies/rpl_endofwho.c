/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_endofwho.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:59:27 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/18 13:27:01 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_endofwho(t_channel *chan, t_users *user, char *buf)
{
	int len;

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, RPL_ENDOFWHO, chan->name);
	circular_send(user->socket, buf, len);
}
