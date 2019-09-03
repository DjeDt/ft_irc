/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nosuchnick.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:51:55 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:51:59 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_nosuchnick(t_users *user, char *nick)
{
	t_data data;

	data.type = ERROR_CODE;
	data.err = ERR_ERRONEUSNICKNAME_ID;
	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server]: <%s> :No such nick/channel.", nick);
	send_data_to_single_user(user->socket, &data);
}
