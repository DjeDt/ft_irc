/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:19:18 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 21:44:12 by ddinaut          ###   ########.fr       */
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
# include <string.h>
# include <errno.h>

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
	INVALID_ARG,
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
# define INVALID_ARG	0
# define INVALID_PORT	1
# define INVALID_SCKT   2
# define INVALID_BIND	3
# define INVALID_LISTEN	4

/* default config */
# define DEFAULT_CHAN	"general"
# define DEFAULT_PORT	"1234"

/* Error/Success */
# define ERR			-1
# define SCS			0

/* fixed value */
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
	char				data[MAX_INPUT_LEN + 1];
}						t_data;

typedef struct			s_fd
{
	int					fd_max;
	fd_set				master;
	fd_set				read;
	fd_set				write;
}						t_fd;

typedef struct			s_users
{
	int					socket;
	char				nick[MAX_NICK_LEN + 1];
	void				*chan;
	struct s_users		*next;
}						t_users;

typedef struct				s_channel_user
{
	t_users					*user;	// ptr to server->users_list->'user_chunk'
	struct s_channel_user	*next;
}							t_channel_user;

typedef struct			s_channel
{
	int					num;		// number of users
	char				name[MAX_CHAN_LEN + 1];
	t_channel_user		*users;		// list of connected users
	struct s_channel	*next;		// next channel
}						t_channel;

typedef struct			s_server
{
	int					port;
	int					sock;
	t_fd				info;
	t_users				*users;
	t_channel			*channel;
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
bool					send_data_to_single(int fd, char *data, size_t size);
bool					send_data_to_spec_chan(t_channel *chan, t_data data, char *nick);
bool					send_data_to_channel(t_channel *chan, t_data data, char *name, char *nick);

/* users */
void					generate_guest_pseudo(char *pseudo, int id);
t_users					*user_create(int socket);
void					user_push(t_users **users, t_users *chunk);
void					user_add(t_users **users, int socket);
void					user_remove(t_users **users, int id);
t_users					*user_search_by_id(t_users *users, int id);
t_users					*user_search_by_name(t_users *users, const char *name);

/* channels */
//void					print_chan(t_channel*chan);
t_channel				*channel_create(char *name);
t_channel				*channel_add(t_channel **chan, char *name);
t_channel				*channel_search(t_channel *chan, char *name);
void					channel_delete(t_channel **channel, char *name);

/* channel users */
void print_channel_user(t_channel_user *chan);
t_channel_user			*channel_user_create(t_users *usr);
t_channel_user			*channel_user_search(t_channel_user *chus, int off);
bool					channel_user_add(t_channel_user **chan, t_users *user);
bool					channel_user_remove(t_channel_user **chan, t_users *user);
void					channel_user_remove_full(t_channel *chan, t_users *users);

/* commands */
void					irc_help(t_server *server, char **command, int off);
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
void					get_date(char *buf);
ssize_t					_strlen(const char *str);
int						arrlen(char **arr);
char					*_strchr(const char *str, char c);
void					*_memset(void *data, char c, size_t size);
void					*_memcpy(void *dst, void *src, size_t n);
void					logger(const char *log, FILE *fd);
char					**_strtok(const char *str, const char *delim);
int						_memcmp(const void *s1, const void *s2, size_t n);
void					_itoa(char *str, int n);
int						_isspace(char c);
char					*_strndup(const char *src, size_t n);


/* error handler */
void					error(int num, const char *err);
void					invalid_arg(const char *str);
void					invalid_port(const char *str);
void					invalid_socket(const char *str);
void					invalid_bind(const char *err);
void					invalid_listen(const char *err);

#endif
