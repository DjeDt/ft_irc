/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:26:02 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/21 17:34:12 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	free_command(char **command)
{
	int count;

	count = 0;
	if (command != NULL)
	{
		while (command[count] != NULL)
		{
			free(command[count]);
			count++;
		}
		free(command);
	}
}

t_command g_func_ptr[] =
{
//	{ "/help", irc_help },
	{ "/nick", irc_nick },
	{ "/list", irc_list },
	{ "/join", irc_join },
	{ "/leave", irc_leave },
	{ "/who", irc_who },
	{ "/msg", irc_msg },
	{ "/connect", irc_connect },
	{ "/quit", irc_quit },
	{ "/shutdown", irc_shutdown }
};

bool	manage_command(t_server *server, char **command, int off)
{
	int		count;
	int		func_num;

	count = 0;
	func_num = sizeof(g_func_ptr) / sizeof(g_func_ptr[0]);
	while (count < func_num)
	{
		if (_memcmp(command[0], g_func_ptr[count].name, _strlen(command[0])) == 0)
		{
			((t_func*)g_func_ptr[count].func)(server, command, off);
			return (true);
		}
		count++;
	}
	return (false);
}

void	interpreter(t_server *server, t_data data, int off)
{
	char **command;

	if (data.data[0] == '/')
	{
		if ((command = _strtok(data.data, " \n\r\t")) == NULL)
			return ;
		manage_command(server, command, off);
		free_command(command);
	}
	else
	{
		// send user message
		puts("NO COMMAND");
	}
}
