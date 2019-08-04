/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:16:48 by ddinaut           #+#    #+#             */
/*   Updated: 2019/07/29 15:13:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void    free_command(char **command)
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

int     command_size(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i] && _isspace(cmd[i]) != 0)
        i++;
    return (i);
}

bool    split_command(char **command, const char *data)
{
    int     size;
    char    *ptr;

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

t_command g_func_ptr[] =
{
	{ "/help", irc_help },
	{ "/nick", irc_nick },
	{ "/list", irc_list },
	{ "/join", irc_join },
	{ "/leave", irc_leave },
	{ "/who", irc_who },
	{ "/msg", irc_msg },
	{ "/connect", wrapper_connect },
	{ "/quit", irc_quit }
};

bool	manage_command(t_interface *inter, t_list_user *user, char **command)
{
	int count;
    int func_num;

    count = 0;
    func_num = sizeof(g_func_ptr) / sizeof(g_func_ptr[0]);
    while (count < func_num)
    {
        if (_memcmp(g_func_ptr[count].name, command[0], _strlen(g_func_ptr[count].name)) == 0)
        {
            ((t_func*)g_func_ptr[count].func)(inter, user, command);
            return (true);
        }
        count++;
    }
	refresh_top_interface(inter, "'%s': command not found. use '/help' to list command.\n", command[0]);
    return (false);
}

void	interpreter(t_interface *inter, t_list_user *user)
{
    char *command[3];

	if (user->input[0] == '/')
    {
        _memset(command, 0x0, sizeof(char*) * 3);
        if (split_command(command, user->input) != true)
            return ;
		manage_command(inter, user, command);
        free_command(command);
    }
    else if (user->connected == true)
		send_data(inter, user);
}
