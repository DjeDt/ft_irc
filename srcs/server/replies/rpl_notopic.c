/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_notopic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:58:59 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 16:59:03 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_notopic(t_channel *channel, t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + 3] = {0};

	len = snprintf(buf, MAX_INPUT_LEN + 3, RPL_NOTOPIC, channel->name);
	circular_send(user->socket, buf, len);
}
