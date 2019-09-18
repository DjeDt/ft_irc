/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needmoreparams.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:58:12 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/18 13:27:38 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_needmoreparams(t_users *user, char *command)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, ERR_NEEDMOREPARAMS, command);
	circular_send(user->socket, buf, len);
}
