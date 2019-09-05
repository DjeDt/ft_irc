/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:19:18 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 23:28:36 by ddinaut          ###   ########.fr       */
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

# include "replies.h"

/*
** Enum
*/
enum e_type
{
	ERROR_CODE,
	MESSAGE_CODE
};

/*
** Defines
*/
# define DEFAULT_PORT	"1234"
# define CRLF			"\r\n"
# define CRLF_LEN		2
# define CRLF_HEX		0x0a0d

# define ERROR			-1
# define SUCCESS		0

# define MAX_QUEUE		5
# define MAX_NICK_LEN	16
# define MAX_CHAN_LEN	200
# define MAX_TOPIC_LEN	128
# define MAX_INPUT_LEN	512

/*
** Typedef
*/
typedef struct			s_command
{
	char				name[16];
	int					name_len;
	void				*func;
}						t_command;

typedef struct			s_data
{
	enum e_type			type;
	int					err;
	int					len;
	char				data[MAX_INPUT_LEN + 3];

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
	int					nick_len;
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
	int					name_len;
	char				name[MAX_CHAN_LEN + 1];
	char				*topic;
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

// server -> channel -> channel_user -> user;

typedef void (*t_error) (const char *err);
typedef void (t_func) (t_server *server, t_users *user, char **command);

/*
** Functions
*/

/* core */
bool					initialize(t_server *server, const char *str);
bool					running(t_server *server);
void					interpreter(t_server *server, t_data data, int off);

bool					receive_data(int off, t_data *data);
bool					send_data_to_single_user(int socket, t_data *data);

/* users */
void					generate_guest_pseudo(char *pseudo, int id);
t_users					*user_create(int socket);
void					user_push(t_users **users, t_users *chunk);
void					user_add(t_users **users, int socket);
void					user_remove(t_users **users, int id);
t_users					*user_search_by_id(t_users *users, int id);
t_users					*user_search_by_name(t_users *users, const char *name);

/* channels */
t_channel				*channel_create(char *name);
t_channel				*channel_add(t_channel **chan, char *name);
t_channel				*channel_search(t_channel **chan, char *name);
void					channel_delete(t_channel **channel, char *name);

/* channel users */
t_channel_user			*channel_user_create(t_users *usr);
t_channel_user			*channel_user_search(t_channel_user *chus, int off);
bool					channel_user_add(t_channel_user **chan, t_users *user);
bool					channel_user_remove(t_channel_user **chan, t_users *user);
void					channel_user_remove_all(t_channel_user **user_list);
void					channel_user_remove_full(t_channel **chan, t_users *users);

/* commands */
void					irc_help(t_server *server, t_users *user, char **command);
void					irc_nick(t_server *server, t_users *user, char **command);
void					irc_list(t_server *server, t_users *user, char **command);
void					irc_join(t_server *server, t_users *user, char **command);
void					irc_leave(t_server *server, t_users *user, char **command);
void					irc_who(t_server *server, t_users *user, char **command);
void					irc_msg(t_server *server, t_users *user, char **command);
void					irc_connect(t_server *server, t_users *user, char **command);
void					irc_topic(t_server *server, t_users *user, char **command);
void					irc_quit(t_server *server, t_users *user, char **command);
void					irc_kill(t_server *server, t_users *user, char **command);

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

/* replies */
void					err_unknow_command(t_users *user, char *command);
void					err_notonchannel(t_users *user, char *name);
void					err_nosuchchannel(t_users *user, char *channel);
void					err_toomanychannels(t_users *user, char *chan_name);
void					err_needmoreparams(t_users *user, char *command);
void					err_nicknameinuse(t_users *user, char *nick);
void					err_erroneusnickname(t_users *user, char *nick);
void					err_erroneuschanname(t_users *user, char *name);
void					err_nosuchnick(t_users *user, char *nick);

void					rpl_topic(t_channel *channel, t_users *user);
void					rpl_notopic(t_channel *channel, t_users *user);
void					rpl_whoreply(t_channel *chan, t_users *user, t_data *data, char *nick);
void					rpl_endofwho(t_channel *chan, t_users *user, t_data *data);
void					rpl_namreply(t_channel *chan, t_users *user, t_data *data, char *nick);
void					rpl_endofnames(t_channel *chan, t_users *user, t_data *data);

#endif
