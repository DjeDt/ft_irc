/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:24:19 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/05 14:05:34 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <ncurses.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <time.h>
# include <unistd.h>
# include <wchar.h>
# include <errno.h>
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# include "lib.h"

/*
** Defines
*/
# define ERROR			-1
# define SUCCESS		0

# define DEFAULT_PORT	"1234"
# define LOCALHOST		"localhost"

# define CONNECT_LEN	7
# define QUIT_LEN		5

# define CRLF			2
# define LINE_START		1
# define CURSOR_START	3
# define BOX_INPUT_LEN	3
# define MAX_INPUT_LEN	510
# define MAX_NICK_LEN	16

# define IPV4_TYPE		4
# define IPV6_TYPE		6

# define BASIC_PORT_STR "Connecting to '%s' using default port '%s'"

typedef struct			s_interface
{
	WINDOW				*top;
	WINDOW				*bot;
	bool				status;
	int					off;
	int					line;
	int					cursor;
	int					curmax;
	int					len;
}						t_interface;

typedef struct			s_client
{
	int					fd_max;
	fd_set				read;
	fd_set				write;
	fd_set				master;
}						t_client;

typedef struct			s_circular
{
	int					head;
	int					tail;
	int					len;
	char				buf[MAX_INPUT_LEN + CRLF];
}						t_circular;

typedef struct			s_user
{
	int					socket;
	bool				running;
	bool				connected;
	char				input[MAX_INPUT_LEN + CRLF];
	t_circular			read;
	t_client			client;
}						t_user;

typedef void	(t_func) \
	(t_interface *inter, t_user *user, char **command);

/*
** Core
*/
void					running(t_interface *inter, t_user *user);
void					interpreter(t_interface *inter, t_user *user);

bool					circular_get(t_interface *inter, t_user *user);
void					circular_send(t_interface *inter, t_user *user);
void					circular_push(t_circular *circ, char *data, int size);

bool					search_for_crlf(char *buf, int head, int size);
void					extract_and_update(t_circular *circ, char *final);

/* command */
void					wrapper_connect(t_interface *inter, \
										t_user *user, char **command);
bool					irc_connect(t_interface *inter, t_user *user,
									char *s_ip, char *s_port);

/* interface */
bool					init_interface(t_interface *inter);
void					refresh_top_interface(t_interface *inter, \
												char *input, ...);
void					refresh_bot_interface(t_interface *inter, char *input);
void					stop_interface(t_interface *inter);

/* readline */
bool					do_key_left(t_interface *inter, char *input);
bool					do_key_right(t_interface *inter, char *input);
bool					insert_char(t_interface *inter, char *input, int c);
bool					delete_char(t_interface *inter, char *input);

#endif
