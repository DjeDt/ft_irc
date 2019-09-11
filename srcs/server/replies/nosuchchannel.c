/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nosuchchannel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:34:04 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 16:57:30 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_nosuchchannel(t_users *user, char *channel)
{
	int		len;
	char	buf[MAX_INPUT_LEN + 3];

	len = snprintf(buf, MAX_INPUT_LEN + 3, ERR_NOSUCHCHANNEL, channel);
	circular_send(user->socket, buf, len);
}
