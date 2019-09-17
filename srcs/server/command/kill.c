/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:09 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 15:14:41 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	irc_kill(t_server *server, t_users *user, char **command)
{
	(void)server;
	(void)command;
	(void)user;
	printf("[%s] kill\n", command[0]);
}
