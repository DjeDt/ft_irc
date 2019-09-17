/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:26:02 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/13 17:39:47 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_command g_func[] =
{
	{ "/help", 5, irc_help },
	{ "/nick", 5, irc_nick },
	{ "/list", 5, irc_list },
	{ "/join", 5, irc_join },
	{ "/leave", 6, irc_leave },
	{ "/topic", 6, irc_topic },
	{ "/who", 4, irc_who },
	{ "/msg", 4, irc_msg },
	{ "/quit", 5, irc_quit },
	{ "/kill", 5, irc_kill }
};

static bool	handle_command(t_server *server, t_users *user, char **command)
{
	int		len;
	int		count;
	int		cmp_len;
	int		func_num;

	count = 0;
	len = ft_strlen(command[0]);
	func_num = sizeof(g_func) / sizeof(g_func[0]);
	while (count < func_num)
	{
		cmp_len = len > g_func[count].name_len ? len : g_func[count].name_len;
		if (ft_strncmp(g_func[count].name, command[0], cmp_len) == 0)
		{
			((t_func*)g_func[count].func)(server, user, command);
			return (true);
		}
		count++;
	}
	if (FD_ISSET(user->socket, &server->info.write))
		err_unknow_command(user, command[0]);
	return (false);
}

static void	handle_message(t_server *server, t_users *user, char *final)
{
	int				len;
	char			test[MAX_INPUT_LEN + 3];
	t_channel_user	*usr_list;

	ft_memset(test, 0x0, MAX_INPUT_LEN + 3);
	if (user->chan == NULL)
	{
		len = snprintf(test, MAX_INPUT_LEN + 3, "Please join channel.\r\n");
		circular_send(user->socket, test, len);
		return ;
	}
	usr_list = ((t_channel*)user->chan)->users;
	if (usr_list == NULL)
		return ;
	len = snprintf(test, MAX_INPUT_LEN + 3, "[%s] %s : %s\r\n", \
		((t_channel*)user->chan)->name, user->nick.nick, final);
	while (usr_list != NULL)
	{
		if (FD_ISSET(usr_list->user->socket, &server->info.write))
			circular_send(usr_list->user->socket, test, len);
		usr_list = usr_list->next;
	}
}

void		interpreter(t_server *server, t_users *user)
{
	char	*cmd[3];
	char	final[MAX_INPUT_LEN + 3];

	ft_memset(cmd, 0x0, sizeof(char*) * 3);
	extract_and_update(&user->circ, final);
	if (final[0] == '/')
	{
		if (command_split(cmd, final) != true)
			return ;
		handle_command(server, user, cmd);
		command_free(cmd);
	}
	else
	{
		if (FD_ISSET(user->socket, &server->info.write))
			handle_message(server, user, final);
	}
}
