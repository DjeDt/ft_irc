/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:26:02 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/26 22:07:16 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

// h <nickname>
/* void	irc_nick(t_server *server, char **command, int off) */
/* { */
/* 	int		len; */
/* 	t_users *user; */

/* 	if (arrlen(command) > 1) */
/* 	{ */
/* 		len = _strlen(command[1]); */
/* 		if (len > MAX_NICK_LEN) */
/* 			return ; */
/* 		user = search_user(&server->users, off); */
/* 		if (user != NULL) */
/* 		{ */
/* 			_memset(user->nick, 0x0, MAX_NICK_LEN); */
/* 			_memcpy(user->nick, command[1], len); */
/* 		} */

/* 		printf("[+] [%s] NICK set to '%s'\n", command[0], user->nick); */
/* 		return ; */
/* 	} */
/* 	printf("[-] [%s] NICK failed\n", command[0]); */
/* } */

/* // /join <channel> <?passwd?> */
/* void	irc_join(t_server *server, char **command, int off) */
/* { */
/* 	(void)server; */
/* 	(void)command; */
/* 	(void)off; */
/* 	printf("[%s] JOIN\n", command[0]); */
/* } */

/* // /leave <channel> */
/* void	irc_leave(t_server *server, char **command, int off) */
/* { */
/* 	(void)server; */
/* 	(void)command; */
/* 	(void)off; */
/* 	printf("[%s] JOIN\n", command[0]); */
/* } */

/* // who <users> */
/* void	irc_who(t_server *server, char **command, int off) */
/* { */
/* 	t_users *user; */

/* 	if (server->users != NULL) */
/* 	{ */
/* 		user = server->users; */
/* 		send_data(off, "Connected users:", 16, 0); */
/* 		while (user != NULL) */
/* 		{ */
/* 			send_data(off, user->nick, _strlen(user->nick), 0); */
/* 			user = user->next; */
/* 		} */
/* 	} */
/* 	printf("[%s] WHO\n", command[0]); */
/* } */

/* // msg <nickname> <message> */
/* void	irc_msg(t_server *server, char **command, int off) */
/* { */
/* 	int		len; */
/* 	t_users *user; */

/* 	(void)off; */
/* 	len = arrlen(command); */
/* 	if (len == 3 && server->users != NULL) */
/* 	{ */
/* 		user = server->users; */
/* 		len = _strlen(command[1]); */
/* 		while (user != NULL) */
/* 		{ */
/* 			if (_memcmp(command[1], user->nick, len) == 0) */
/* 			{ */
/* 				len = _strlen(command[2]); */
/* 				send_data(user->socket, command[2], len, 0); */
/* 				return ; */
/* 			} */
/* 			user = user->next; */
/* 		} */
/* 	} */
/* 	printf("[%s] ERROR MSG\n", command[0]); */
/* } */

/* // quit */
/* void	irc_quit(t_server *server, char **command, int off) */
/* { */
/* 	if (server->users != NULL) */
/* 	{ */
/* 		remove_user(&server->users, off); */
/* 		close(off); */
/* 		FD_CLR(off, &server->client.master); */
/* 		printf("[-] [%s] CLOSED connection from %d\n", command[0], off); */
/* 	} */
/* 	printf("[%s] QUIT\n", command[0]); */
/* } */

/* // client side */
/* void	irc_connect(t_server *server, char **command, int off) */
/* { */
/* 	(void)server; */
/* 	(void)command; */
/* 	(void)off; */
/* 	printf("[%s] CONNECT\n", command[0]); */
/* } */

/* // close the server */
/* void	irc_shutdown(t_server *server, char **command, int off) */
/* { */
/* 	(void)server; */
/* 	(void)command; */
/* 	(void)off; */
/* 	printf("[%s] SHUTDOWN\n", command[0]); */
/* } */

void	invalid_command(t_server *server, char **command, int off)
{
	(void)server;
	(void)command;
	(void)off;
	printf("[%s] INVALID\n", command[0]);
}

void	free_command(t_data *data, char **command)
{
	int count;

	count = 0;
	_memset(data, 0, sizeof(*data));
	while(command[count] != NULL)
	{
		free(command[count]);
		count++;
	}
	free(command);
}

void	irc_nick(){}
void irc_join(){}
void irc_who(){}
void irc_msg(){}
void irc_connect(){}
void irc_quit(){}
void irc_shutdown(){}

t_command g_func_ptr[] =
{
	{ "/nick", irc_nick },
	{ "/join", irc_join },
	{ "/who", irc_who },
	{ "/msg", irc_msg },
	{ "/connect", irc_connect },
	{ "/quit", irc_quit },
	{ "/shutdown", irc_shutdown }
};


bool	interpreter(t_server *server, t_data data, int off)
{
	int		count;
	int		func_num;
	char	**command;

	count = 0;
	func_num = sizeof(g_func_ptr) / sizeof(g_func_ptr[0]);
	if ((command = _strtok(data.data, " \n\r\t")) == NULL)
		return (false);
	while (count < func_num)
	{
		if (_memcmp(command[0], g_func_ptr[count].name, _strlen(command[0])) == 0)
		{
			((t_func*)g_func_ptr[count].func)(server, command, off);
			free_command(&data, command);
			return (true);
		}
		count++;
	}
//	invalid_command(server, command, off);
	free_command(&data, command);
	return (false);
}
