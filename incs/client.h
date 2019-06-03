/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:24:19 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/28 15:56:06 by ddinaut          ###   ########.fr       */
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

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>

/*
** Defines
*/

# define CURSOR_START	3

# define BOX_INPUT_LEN	3
# define MAX_INPUT_LEN	512
# define MAX_NICK_LEN	16

/* Struct */
typedef struct			s_interface
{
	WINDOW				*top;
	WINDOW				*bot;
	int					off;
	int					line;
	int					cursor;
	int					curmax;
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
	int					new;
	int					fd_max;
	fd_set				read;
	fd_set				write;
}						t_client;

typedef struct			s_list_user
{
	int					socket;
	int					statut;
	char				nick[MAX_NICK_LEN];
	char				input[MAX_INPUT_LEN];
	t_client			client;
	struct sockaddr_in	addr;
}						t_list_user;

typedef void (t_func) (t_interface *inter, t_list_user *user, char **command);

/*
** Core
*/
void					running(t_interface *inter, t_list_user *user);
void					interpreter(t_interface *inter, t_list_user *user);

bool    receive_data(int off, t_data *data, size_t size, int flag);
/* command */
bool					connect_to_server(t_list_user *user, const char *s_ip, const char *s_port);

/* interface */
bool					init_interface(t_interface *inter);
void					refresh_top_interface(t_interface *inter, char *input);
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
