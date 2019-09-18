/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:08:40 by Dje               #+#    #+#             */
/*   Updated: 2019/09/18 09:08:42 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_welcome(t_users *user)
{
	int		len;
	char	data[MAX_INPUT_LEN + 3];

	len = snprintf(data, MAX_INPUT_LEN + 3, \
		"Welcome '%s' !\n Please use /join or /help to get started!\r\n", \
		user->nick.nick);
	circular_send(user->socket, data, len);
}
