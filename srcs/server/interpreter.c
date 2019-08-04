/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:26:02 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 21:51:14 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_command g_func_ptr[] =
{
	{ "/help", irc_help },
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

bool	handle_command(t_server *server, char **command, int off)
{
	int		count;
	int		func_num;

	count = 0;
	func_num = sizeof(g_func_ptr) / sizeof(g_func_ptr[0]);
	while (count < func_num)
	{
		if (_memcmp(g_func_ptr[count].name, command[0], _strlen(g_func_ptr[count].name)) == 0)
		{
			((t_func*)g_func_ptr[count].func)(server, command, off);
			return (true);
		}
		count++;
	}
	if (FD_ISSET(off, &server->info.write))
		send_data_to_single(off, "command not found", 17);
	return (false);
}

void	handle_message(t_server *server, t_data d, int off)
{
	t_data			data;
	t_users			*user;
	t_channel_user	*usr_list;

	user = user_search_by_id(server->users, off);
	if (user->chan == NULL)
		return ;
	usr_list = ((t_channel*)user->chan)->users;

	data.len = snprintf(data.data, MAX_INPUT_LEN, "[%s]> %s", user->nick, d.data);
	while (usr_list != NULL)
	{
		if (FD_ISSET(usr_list->user->socket, &server->info.write))
			send_data_to_single(usr_list->user->socket, data.data, data.len);
		usr_list = usr_list->next;
	}
}

void	interpreter(t_server *server, t_data data, int off)
{
	char	*command[3];

	if (data.data[0] == '/')
	{
		if (split_command(command, data.data) != true)
			return ;
		handle_command(server, command, off);
		free_command(command);
	}
	else
	{
		if (FD_ISSET(off, &server->info.write))
			handle_message(server, data, off);
	}
}
