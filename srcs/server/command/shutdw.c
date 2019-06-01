/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 09:04:09 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/31 14:42:25 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

// close the server
void	irc_shutdown(t_server *server, char **command, int off)
{
	(void)server;
	(void)command;
	(void)off;
	printf("[%s] SHUTDOWN\n", command[0]);
}
