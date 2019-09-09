/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unknow_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:55:07 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:49:36 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_unknow_command(t_users *user, char *command)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, ERR_UNKNOWNCOMMAND, command);
	circular_send(user->socket, buf);
	return ;
}
