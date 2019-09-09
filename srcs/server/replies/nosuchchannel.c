/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nosuchchannel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:34:04 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:51:00 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_nosuchchannel(t_users *user, char *channel)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, ERR_NOSUCHCHANNEL, channel);
	circular_send(user->socket, buf);
}
