/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nicknameinuse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:09:42 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:51:37 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_nicknameinuse(t_users *user, char *nick)
{
	t_data data;

	data.type = ERROR_CODE;
	data.err = ERR_NICKNAMEINUSE_ID;
	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server]: <%s> :Nickname is already in use.", nick);
	send_data_to_single_user(user->socket, &data);
}
