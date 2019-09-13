/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:24:19 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/13 17:16:23 by ddinaut          ###   ########.fr       */
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

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>

/*
** Defines
*/

# define ERROR			-1
# define SUCCESS		0

# define CRLF           "\n"
# define CRLF_LEN       2
# define CRLF_HEX       0x0a

# define DEFAULT_PORT	"1234"
# define LOCALHOST		"127.0.0.1"

# define CURSOR_START	3
# define BOX_INPUT_LEN	3
# define MAX_INPUT_LEN	512
# define MAX_NICK_LEN	16

/* Struct */
typedef struct			s_interface
{
	WINDOW				*top;
	WINDOW				*bot;
	bool				status;
	int					off;	// cursor offset in str
	int					line;	// printable line for top
	int					cursor;	// where is the visible cursor
	int					curmax;	// max visible cursor
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
	char				buf[MAX_INPUT_LEN + 3];
}						t_circular;

typedef struct			s_list_user
{
	int					socket;
	bool				running;
	bool				connected;
	char				input[MAX_INPUT_LEN + 3];
	t_circular			circ;
	t_client			client;
}						t_list_user;

typedef void (t_func) (t_interface *inter, t_list_user *user, char **command);

/*
** Core
*/
void					running(t_interface *inter, t_list_user *user);
void					interpreter(t_interface *inter, t_list_user *user);

bool                    circular_get(t_interface *inter, t_list_user *user);
void                    circular_send(t_interface *inter, t_list_user *user);
void                    circular_push(t_circular *circ, char *data, int size);

bool					search_for_crlf(char *buf, int head, int size);
void					extract_and_update(t_circular *circ, char *final);

/* command */
void					wrapper_connect(t_interface *inter, t_list_user *user, char **command);
bool					irc_connect(t_interface *inter, t_list_user *user, const char *s_ip, const char *s_port);

/* interface */
bool					init_interface(t_interface *inter);
void					refresh_top_interface(t_interface *inter, char *input, ...);
void					refresh_bot_interface(t_interface *inter, char *input);

/* readline */
bool					do_key_left(t_interface *inter, char *input);
bool					do_key_right(t_interface *inter, char *input);
bool					do_key_up(t_interface *inter, char *input);
bool					do_key_down(t_interface *inter, char *input);
bool					insert_char(t_interface *inter, char *input, int c);
bool					delete_char(t_interface *inter, char *input);

/* lib */
ssize_t                 _strlen(const char *str);
int                     arrlen(char **arr);
char                    *_strchr(const char *str, char c);
void                    *_memset(void *data, char c, size_t size);
void                    *_memcpy(void *dst, void *src, size_t n);
void                    logger(const char *log, FILE *fd);
char                    **_strtok(const char *str, const char *delim);
int                     _memcmp(const void *s1, const void *s2, size_t n);
void                    _itoa(char *str, int n);
int                     _isspace(char c);
char                    *_strndup(const char *src, size_t n);

#endif
