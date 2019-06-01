/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:24 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/31 09:04:25 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

// client side
void	irc_connect(t_server *server, char **command, int off)
{
	(void)server;
	(void)command;
	(void)off;
	printf("[%s] CONNECT\n", command[0]);
}
