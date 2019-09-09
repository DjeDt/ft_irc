/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nosuchchannel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:34:04 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:51:00 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_nosuchchannel(t_users *user, char *channel)
{
	t_data data;

	data.type = ERROR_CODE;
	data.err = ERR_NOSUCHCHANNEL_ID;
	data.len = snprintf(data.data, MAX_INPUT_LEN, ERR_NOSUCHCHANNEL, channel);
	send_data_to_single_user(user->socket, &data);
}
