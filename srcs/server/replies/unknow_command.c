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
	t_data data;

	data.type = ERROR_CODE;
	data.err = ERR_UNKNOWNCOMMAND_ID;
	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server]: <%s> :Unknow command", command);
	send_data_to_single_user(user->socket, &data);
	return ;
}
