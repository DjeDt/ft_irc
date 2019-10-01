/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toomanyargument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:32:24 by Dje               #+#    #+#             */
/*   Updated: 2019/10/01 11:34:49 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_toomanyarguments(t_users *user, char *command)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, ERR_TOOMANYARGUMENTS, command);
	circular_send(user->socket, buf, len);
}
