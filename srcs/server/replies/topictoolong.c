/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topictoolong.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 13:30:23 by Dje               #+#    #+#             */
/*   Updated: 2019/09/18 13:32:05 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_topictoolong(t_users *user, char *topic)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, TOPIC_TOO_LONG, topic);
	circular_send(user->socket, buf, len);
}
