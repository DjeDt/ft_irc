/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_endofnames.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:59:51 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 16:59:54 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_endofnames(t_channel *chan, t_users *user, char *buf)
{
	int	len;

	memset(buf, 0x0, MAX_INPUT_LEN + 3);
	len = snprintf(buf, MAX_INPUT_LEN + 3, RPL_ENDOFNAMES, chan->name);
	circular_send(user->socket, buf, len);
}
