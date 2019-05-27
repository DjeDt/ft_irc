/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:19:18 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/21 17:03:32 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

/*
** Includes
*/
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <time.h>
# include <unistd.h>

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>


/*
** Enum
*/

enum e_error
{
	MISSING_ARG,
	INVALID_PORT,
	INVALID_SCKT,
	INVALID_BIND
};

enum e_statut
{
	GUEST,
	LOGGED
};

/*
** Defines
*/
# define MISSING_ARG	0
# define INVALID_PORT	1
# define INVALID_SCKT   2
# define INVALID_BIND	3

/* Error/Success */
# define ERR			-1
# define SCS			0

# define MAX_QUEUE		5
# define MAX_NICK_LEN	16
# define MAX_CHAN_LEN	50
# define MAX_INPUT_LEN	512

# define GUEST			0
# define LOGGED			1

/*
** Typedef
*/

typedef struct			s_command
{
	char				name[16];
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
	fd_set				master;
	fd_set				read;
	fd_set				write;
}						t_client;

typedef struct			s_list_user
{
	int					socket;
	int					statut;
	char				nick[MAX_NICK_LEN];
	struct sockaddr_in	addr;
	struct s_list_user	*next;
}						t_list_user;

typedef struct			s_channel
{
	int					num;
	fd_set				connected;
	char				name[MAX_CHAN_LEN];
	struct s_channel	*next;
}						t_channel;

typedef struct			s_server
{
	int					port;
	int					socket;
	t_client			client;
	t_channel			*chan;
	t_list_user			*users;
}						t_server;

typedef void (*t_error) (const char *err);
typedef void (t_func) (t_server *server, char **command, int off);

/*
** Functions
*/

/* core */
bool					initialize(t_server *server, const char *str);
bool					running(t_server *server);
void					interpreter(t_server *server, t_data data, int off);

bool					receive_data(int off, t_data *data, size_t size, int flag);

void					send_welcome(int off);
bool					send_to_all(t_server *server, t_client *client, t_data data, int count);
bool					send_data(int fd, char *data, int size, int flag);

/* users */
void					generate_guest_pseudo(char *pseudo, int id);
t_list_user				*create_new_user(int socket);
void					push_new_user(t_list_user **users, t_list_user *chunk);
void					add_users(t_list_user **users, int socket);
void					remove_user(t_list_user **users, int id);
t_list_user				*search_user(t_list_user *users, int id);

/* channels */
void					print_chan(t_channel*chan);
t_channel				*create_channel(char *name);
t_channel				*add_channel(t_channel **chan, char *name);
t_channel				*search_channel(t_channel *chan, char *name);
void					delete_channel(t_channel **channel, char *name);

/* commands */
//void					irc_help(t_server *server, char **command, int off);
void					irc_nick(t_server *server, char **command, int off);
void					irc_list(t_server *server, char **command, int off);
void					irc_join(t_server *server, char **command, int off);
void					irc_leave(t_server *server, char **command, int off);
void					irc_who(t_server *server, char **command, int off);
void					irc_msg(t_server *server, char **command, int off);
void					irc_connect(t_server *server, char **command, int off);
void					irc_quit(t_server *server, char **command, int off);
void					irc_shutdown(t_server *server, char **command, int off);

/* lib */
ssize_t					_strlen(const char *str);
int						arrlen(char **arr);
char					*_strchr(const char *str, char c);
void					*_memset(void *data, char c, size_t size);
void					*_memcpy(void *dst, void *src, size_t n);
void					logger(const char *log, FILE *fd);
char					**_strtok(const char *str, const char *delim);
int						_memcmp(const void *s1, const void *s2, size_t n);
void					_itoa(char *str, int n);

/* error handler */
void					error(int num, const char *err);
void					missing_arg(const char *str);
void					invalid_port(const char *str);
void					invalid_socket(const char *str);
void					invalid_bind(const char *err);

#endif
