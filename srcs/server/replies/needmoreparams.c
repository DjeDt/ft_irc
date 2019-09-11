/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needmoreparams.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:58:12 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 16:57:51 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_needmoreparams(t_users *user, char *command)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, ERR_NEEDMOREPARAMS, command);
	circular_send(user->socket, buf, _strlen(buf));
}
