/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notonchannel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:22:49 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:50:38 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_notonchannel(t_users *user, char *name)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, ERR_NOTONCHANNEL, name);
	circular_send(user->socket, buf);
}
