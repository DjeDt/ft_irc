/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notonchannel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:22:49 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:50:38 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_notonchannel(t_users *user, char *name)
{
	t_data data;

	data.type = ERROR_CODE;
	data.err = ERR_NOTONCHANNEL_ID;
	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server]: <%s> :You're not on that channel", name);
	send_data_to_single_user(user->socket, &data);
}
