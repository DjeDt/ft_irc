/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:16:48 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/28 16:09:08 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	free_command(char **command)
{
	int off;

	off = 0;
	while (command[off] != NULL)
	{
		free(command[off]);
		off++;
	}
	free(command);
}

void	manage_command(char **command)
{
	if (_memcmp("quit", command[0], _strlen(command[0])) == 0)
		printf("SKDJFHKSDJHFKSJDHKFJH");
	return ;
}

void	send_data()
{
	return ;
}

void	interpreter(t_interface *inter, t_list_user *user)
{
	(void)inter;
	char **command;

	if (user->input[0] == '/')
	{
		command = _strtok(user->input, " \n\r\t");
		manage_command(command);
		free_command(command);
	}
	else
		send_data();
}
