/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroneuschanname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:58:17 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/12 12:30:56 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_erroneuschanname(t_users *user, char *name)
{
	int		len;
	char	buf[MAX_INPUT_LEN + 3];

	memset(buf, 0x0, MAX_INPUT_LEN + 3);
	len = snprintf(buf, MAX_INPUT_LEN + 3, ERR_ERRONEUSCHANNAME, name);
	circular_send(user->socket, buf, len);
}
