/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:00:11 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 17:00:14 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_list(t_channel *chan, t_users *user, char *buf)
{
	int len;

	len = snprintf(buf, MAX_INPUT_LEN + 3, RPL_LIST, chan->name, chan->num);
	circular_send(user->socket, buf, len);
}
