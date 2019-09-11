/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:26:02 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 20:38:05 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_command g_func_ptr[] =
{
	{ "/help", 5, irc_help },
	{ "/nick", 5, irc_nick },
	{ "/list", 5, irc_list },
	{ "/join", 5, irc_join },
	{ "/leave", 6, irc_leave },
	{ "/topic", 6, irc_topic },
	{ "/who", 4, irc_who },
	{ "/msg", 4, irc_msg },
	{ "/connect", 8, irc_connect },
	{ "/quit", 5, irc_quit },
	{ "/kill", 5, irc_kill }
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

bool	split_command(char **command, const char *final)
{
	int		size;
	char	*ptr;

	ptr = (char*)final;
	size = command_size(ptr);
	if (size > 0)
	{
		if (!(command[0] = _strndup(ptr, size)))
			return (false);
		printf("\tcommand[0] = '%s'\n", command[0]);
		ptr = ptr + (size + 1);
		size = command_size(ptr);
		if (size > 0)
		{
			if (!(command[1] = _strndup(ptr, size)))
				return (false);
			printf("\tcommand[1] = '%s'\n", command[1]);
			ptr = ptr + (size + 1);
			size = _strlen(ptr);
			if (size > 0)
			{
				if (!(command[2] = _strndup(ptr, size)))
					return (false);
				printf("\tcommand[2] = '%s'\n", command[2]);
			}
		}
		return (true);
	}
	return (false);
}

bool	handle_command(t_server *server, t_users *user, char **command)
{
	int		len;
	int		count;
	int		cmp_len;
	int		func_num;

	count = 0;
	len = _strlen(command[0]);
	func_num = sizeof(g_func_ptr) / sizeof(g_func_ptr[0]);

	printf("HANDLE COMMAND 1 : nick = '%s'\n", user->nick.nick);
	printf("==============================\n\n");


	while (count < func_num)
	{
		cmp_len = len > g_func_ptr[count].name_len ? len : g_func_ptr[count].name_len;
		if (_memcmp(g_func_ptr[count].name, command[0], cmp_len) == 0)
		{

			((t_func*)g_func_ptr[count].func)(server, user, command);

			printf("HANDLE COMMAND 2 : nick = '%s'\n", user->nick.nick);
			printf("==============================\n\n");


			return (true);
		}
		count++;
	}

	printf("HANDLE COMMAND 3 : nick = '%s'\n", user->nick.nick);
	printf("==============================\n\n");


	if (FD_ISSET(user->socket, &server->info.write))
		err_unknow_command(user, command[0]);

	printf("HANDLE COMMAND 4 : nick = '%s'\n", user->nick.nick);
	printf("==============================\n\n");


	return (false);
}

void	handle_message(t_server *server, t_users *user, char *final)
{
	int				len;
	char			test[MAX_INPUT_LEN + 3] = {0};
	t_channel_user	*usr_list;


	printf("TEST 1 : nick = '%s'\n", user->nick.nick);
	printf("==============================\n\n");
	if (user->chan == NULL)
		return ;
	usr_list = ((t_channel*)user->chan)->users;
	if (usr_list == NULL)
		return ;
	printf("TEST 2 : nick = '%s'\n", user->nick.nick);
	printf("==============================\n\n");

	len = snprintf(test, MAX_INPUT_LEN, "[%s] %s : %s", ((t_channel*)user->chan)->name, user->nick.nick, final);

	printf("TEST 3 : nick = '%s'\n", user->nick.nick);
	printf("==============================\n\n");

	while (usr_list != NULL)
	{
		if (FD_ISSET(usr_list->user->socket, &server->info.write))
			circular_send(usr_list->user->socket, test, len);
		usr_list = usr_list->next;
	}
}

void	extract_from_circular(char *final, t_circular *circ)
{
	int count;
	int head;

	count = 0;
	head = circ->head;
	while (count < circ->len)
	{
		final[count] = circ->buf[head];
		head = (head + 1) % MAX_INPUT_LEN;
		count++;
	}
	final[count] = '\0';
}

void	interpreter(t_server *server, t_users *user)
{
	char	*cmd[3] = {0};
	char	final[MAX_INPUT_LEN + 3] = {0};

	extract_from_circular(final, &user->circ);
	printf("Extracted from circle : '%s'\n", final);
	printf("==============================\n\n");
	if (final[0] == '/')
	{
		if (split_command(cmd, final) != true)
			return ;

	printf("TEST 4 : nick = '%s'\n", user->nick.nick);
	printf("==============================\n\n");

	handle_command(server, user, cmd);

	printf("TEST 5 : nick = '%s'\n", user->nick.nick);
	printf("==============================\n\n");

	free_command(cmd);

	}
	else
	{
		if (FD_ISSET(user->socket, &server->info.write))
			handle_message(server, user, final);
	}
}
