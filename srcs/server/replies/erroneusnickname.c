/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroneusnickname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:12:52 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 16:58:08 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_erroneusnickname(t_users *user, char *nick)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, ERR_ERRONEUSNICKNAME, nick);
	circular_send(user->socket, buf, _strlen(buf));
}
