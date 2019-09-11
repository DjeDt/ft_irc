/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_endofwho.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:59:27 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 16:59:30 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_endofwho(t_channel *chan, t_users *user, char *buf)
{
	int len;

	len = snprintf(buf, MAX_INPUT_LEN + 3, RPL_ENDOFWHO, chan->name);
	circular_send(user->socket, buf, len);
}
