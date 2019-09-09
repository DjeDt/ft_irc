/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needmoreparams.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:58:12 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:51:18 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_needmoreparams(t_users *user, char *command)
{
	t_data data;

	data.type = ERROR_CODE;
	data.err = ERR_NEEDMOREPARAMS_ID;
	data.len = snprintf(data.data, MAX_INPUT_LEN, ERR_NEEDMOREPARAMS, command);
	send_data_to_single_user(user->socket, &data);
}
