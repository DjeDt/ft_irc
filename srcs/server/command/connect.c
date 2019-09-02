/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/06/05 13:49:47 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

// client side
void	irc_connect(t_server *server, t_users *user, char **command)
{
	(void)server;
	(void)command;
	(void)user;
	printf("[%s] CONNECT\n", command[0]);
}
