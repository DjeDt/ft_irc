/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_kill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 13:55:42 by Dje               #+#    #+#             */
/*   Updated: 2019/10/01 16:14:07 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	init_kill_pass(t_server *server)
{
	int		val;
	int		count;
	char	charset[CHARSET_LEN + 1];

	ft_memcpy(charset, \
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", \
		CHARSET_LEN);
	count = 0;
	srand(time(NULL));
	while (count < KILL_PASS_LEN)
	{
		val = rand() % CHARSET_LEN;
		server->kill_pass[count] = charset[val];
		count++;
	}
	server->kill_pass[count] = '\0';
	printf("[LOG +] Kill pass generated : [%s].\n", server->kill_pass);
}
