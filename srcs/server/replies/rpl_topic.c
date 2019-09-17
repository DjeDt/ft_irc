/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_topic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:58:48 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/12 13:51:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_topic(t_channel *chan, t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + 3];

	len = snprintf(buf, MAX_INPUT_LEN + 3, RPL_TOPIC, chan->name, chan->topic);
	circular_send(user->socket, buf, len);
}
