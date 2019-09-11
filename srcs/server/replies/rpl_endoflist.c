/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_endoflist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:00:22 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 17:00:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_endoflist(t_users *user, char *buf)
{
	int	len;

	len = snprintf(buf, MAX_INPUT_LEN + 3, RPL_ENDOFLIST);
	circular_send(user->socket, buf, len);
}
