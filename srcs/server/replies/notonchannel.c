/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notonchannel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:22:49 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/18 13:27:12 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_notonchannel(t_users *user, char *name)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, ERR_NOTONCHANNEL, name);
	circular_send(user->socket, buf, len);
}
