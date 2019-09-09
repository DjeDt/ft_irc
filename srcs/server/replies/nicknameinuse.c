/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nicknameinuse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:09:42 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:51:37 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_nicknameinuse(t_users *user, char *nick)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, ERR_NICKNAMEINUSE, nick);
	circular_send(user->socket, buf);
}
