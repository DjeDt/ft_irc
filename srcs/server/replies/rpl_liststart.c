/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_liststart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:00:01 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 17:00:05 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_liststart(t_users *user, char *buf)
{
	snprintf(buf, MAX_INPUT_LEN, RPL_LISTSTART);
	circular_send(user->socket, buf, _strlen(buf));
}
