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

void	rpl_list(t_channel *channel, t_users *user, char *buf)
{
	snprintf(buf, MAX_INPUT_LEN, RPL_LIST, channel->name, channel->num);
	circular_send(user->socket, buf, _strlen(buf));
}
