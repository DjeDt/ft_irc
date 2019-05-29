/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:26:02 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/29 18:13:37 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	free_command(char **command)
{
	if (command[0] != NULL)
	{
		free(command[0]);
		if (command[1] != NULL)
		{
			free(command[1]);
			if (command[2] != NULL)
				free(command[2]);
		}
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

int		command_size(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && _isspace(cmd[i]) != 0)
		i++;
	return (i);
}


bool	split_command(char **command, const char *data)
{
	int		size;
	char	*ptr;

	ptr = (char*)data;
	size = command_size(ptr);
	if (size > 0)
	{
		if (!(command[0] = _strndup(ptr, size)))
			return (false);
		ptr = ptr + (size + 1);
		size = command_size(ptr);
		if (size > 0)
		{
			if (!(command[1] = _strndup(ptr, size)))
				return (false);
			ptr = ptr + (size + 1);
			size = _strlen(ptr);
			if (size > 0)
			{
				if (!(command[2] = _strndup(ptr, size)))
					return (false);
			}
		}
		return (true);
	}
	return (false);
}

bool	manage_command(t_server *server, char **command, int off)
{
	int		count;
	int		cmd_len;
	int		func_num;

	count = 0;
	cmd_len = _strlen(command[0]);
	func_num = sizeof(g_func_ptr) / sizeof(g_func_ptr[0]);
	while (count < func_num)
	{
		if (_memcmp(g_func_ptr[count].name, command[0], cmd_len) == 0)
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
	char *command[3];

	if (data.data[0] == '/')
	{
		_memset(command, 0x0, sizeof(char*) * 3);
		if (split_command(command, data.data) != true)
			return ;
		manage_command(server, command, off);
		free_command(command);
	}
	else
	{
		// send user message to channel
		puts("NO COMMAND");
	}
}
