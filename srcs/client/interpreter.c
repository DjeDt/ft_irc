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

void	irc_quit(t_interface *inter, t_list_user *user, char **command)
{
	(void)inter;
	(void)user;
	(void)command;
}


void	irc_msg(t_interface *inter, t_list_user *user, char **command)
{
	if (command[0] != NULL && command[1] != NULL && command[2] != NULL)
	{
		if (send(user->socket, user->input, inter->curmax, 0) < 0)
			refresh_top_interface(inter, "error, can't send message");
	}
}

t_command g_func_ptr[] =
{
    { "/quit", irc_quit },
	{ "/msg", irc_msg }
};

void	unknow_command(t_interface *inter, t_list_user *user, char *command)
{
	(void)inter;
	(void)user;
	mvwprintw(inter->top, inter->line, 1, "unknow command: '%s'\n", command);
	inter->line++;
	wrefresh(inter->top);
}

bool	manage_command(t_interface *inter, t_list_user *user, char **command)
{
	int count;
    int cmd_len;
    int func_num;

    count = 0;
    cmd_len = _strlen(command[0]);
    func_num = sizeof(g_func_ptr) / sizeof(g_func_ptr[0]);
    while (count < func_num)
    {
        if (_memcmp(g_func_ptr[count].name, command[0], cmd_len) == 0)
        {
            ((t_func*)g_func_ptr[count].func)(inter, user, command);
            return (true);
        }
        count++;
    }
	unknow_command(inter, user, command[0]);
    return (false);
}

void	interpreter(t_interface *inter, t_list_user *user)
{
	(void)inter;
    char *command[3];

	if (user->input[0] == '/')
    {
        _memset(command, 0x0, sizeof(char*) * 3);
        if (split_command(command, user->input) != true)
            return ;

        manage_command(inter, user, command);
        free_command(command);
    }
    else
    {
		send(user->socket, user->input, inter->curmax, 0);
    }
}
