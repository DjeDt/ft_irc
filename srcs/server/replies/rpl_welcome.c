/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_welcome.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 13:11:02 by Dje               #+#    #+#             */
/*   Updated: 2019/09/18 13:13:05 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	rpl_welcome(t_users *user)
{
	int		len;
	char	data[MAX_INPUT_LEN + CRLF];

	len = snprintf(data, MAX_INPUT_LEN + CRLF, RPL_WELCOME, user->nick.nick);
	circular_send(user->socket, data, len);
}
