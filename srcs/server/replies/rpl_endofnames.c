/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_endofnames.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:59:51 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/22 15:59:29 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_endofnames(t_channel *chan, t_users *user, char *buf)
{
	int	len;

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, RPL_ENDOFNAMES, chan->name);
	circular_send(user->socket, buf, len);
}
