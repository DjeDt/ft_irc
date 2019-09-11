/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toomanychannels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:57:38 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 16:57:39 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_toomanychannels(t_users *user, char *chan_name)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, ERR_TOOMANYCHANNELS, chan_name);
	circular_send(user->socket, buf, _strlen(buf));
}
