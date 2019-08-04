/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:24:19 by ddinaut           #+#    #+#             */
/*   Updated: 2019/07/29 15:11:04 by ddinaut          ###   ########.fr       */
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
# define DEFAULT_PORT	"1234"

# define CURSOR_START	3
# define BOX_INPUT_LEN	3
# define MAX_INPUT_LEN	512
# define MAX_NICK_LEN	16

/* Struct */
typedef struct			s_interface
{
	WINDOW				*top;
	WINDOW				*bot;
	int					off;	// cursor offset in str
	int					line;	// printable line for top
	int					cursor;	// where is the visible cursor
	int					curmax;	// max visible cursor
}						t_interface;

typedef struct			s_command
{
	char				name[MAX_NICK_LEN];
	void				*func;
}						t_command;

typedef struct			s_data
{
	int					len;
	char				data[MAX_INPUT_LEN];
}						t_data;

typedef struct			s_client
{
	int					fd_max;
	fd_set				read;
	fd_set				write;
}						t_client;

typedef struct			s_list_user
{
	int					socket;
	bool				running;
	bool				connected;
	char				nick[MAX_NICK_LEN + 1];
	char				input[MAX_INPUT_LEN + 1];
	t_client			client;
}						t_list_user;

typedef void (t_func) (t_interface *inter, t_list_user *user, char **command);

/*
** Core
*/
void					running(t_interface *inter, t_list_user *user);
void					interpreter(t_interface *inter, t_list_user *user);

bool				    receive_data(int off, t_data *data, size_t size, int flag);
bool					send_data(t_interface *inter, t_list_user *user);

/* command */
void					irc_msg(t_interface *inter, t_list_user *user, char **command);
void					irc_who(t_interface *inter, t_list_user *user, char **command);
void					irc_help(t_interface *inter, t_list_user *user, char **command);
void					irc_list(t_interface *inter, t_list_user *user, char **command);
void					irc_quit(t_interface *inter, t_list_user *user, char **command);
bool					irc_nick(t_interface *inter, t_list_user *user, char **command);
void					irc_join(t_interface *inter, t_list_user *user, char **command);
void					irc_leave(t_interface *inter, t_list_user *user, char **command);
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
