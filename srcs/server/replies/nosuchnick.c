/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nosuchnick.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:51:55 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:51:59 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_nosuchnick(t_users *user, char *nick)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, ERR_NOSUCHNICK, nick);
	circular_send(user->socket, buf);
}
