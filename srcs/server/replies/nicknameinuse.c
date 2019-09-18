/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nicknameinuse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:09:42 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/18 13:27:24 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_nicknameinuse(t_users *user, char *nick)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, ERR_NICKNAMEINUSE, nick);
	circular_send(user->socket, buf, len);
}
