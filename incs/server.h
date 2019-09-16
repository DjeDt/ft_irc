/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:19:18 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/13 17:36:13 by ddinaut          ###   ########.fr       */
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
# include "lib.h"

/*
** Defines
*/
# define DEFAULT_PORT	"1234"

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
typedef struct				s_command
{
	char					name[16];
	int						name_len;
	void					*func;
}							t_command;

typedef struct				s_fd
{
	int						fd_max;
	fd_set					read;
	fd_set					write;
	fd_set					master;
}							t_fd;

typedef struct				s_nick
{
	int						nick_len;
	char					nick[MAX_NICK_LEN + 1];
}							t_nick;

typedef struct				s_circular
{
	int						head;
	int						tail;
	int						len;
	char					buf[MAX_INPUT_LEN + 3];
	char					received[MAX_INPUT_LEN + 3];
}							t_circular;

typedef struct				s_users
{
	int						socket;
	t_nick					nick;
	t_circular				circ;
	void					*chan;
	struct s_users			*next;
}							t_users;

typedef struct				s_channel_user
{
	t_users					*user;
	struct s_channel_user	*next;
}							t_channel_user;

typedef struct				s_channel
{
	int						num;
	int						name_len;
	char					name[MAX_CHAN_LEN + 1];
	char					*topic;
	t_channel_user			*users;
	struct s_channel		*next;
}							t_channel;

typedef struct				s_server
{
	int						port;
	int						sock;
	t_fd					info;
	t_users					*users;
	t_channel				*channel;
}							t_server;

typedef void (*t_error) (const char *err);
typedef void (t_func) (t_server *server, t_users *user, char **command);

/*
** Functions
*/
/* core */
bool					initialize(t_server *server, const char *str);
bool					running(t_server *server);
void					interpreter(t_server *server, t_users *user);

/* Circular buffer */
bool					circular_get(t_users *user);
void					circular_send(int socket, char *data, int size);
void					circular_push(t_circular *circ, char *data, int size);
bool					search_for_crlf(char *buf, int head, int size);
void					extract_and_update(t_circular *circ, char *final);

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
void					command_free(char **command);
int						command_size(char *command);
bool					command_split(char **command, const char *final);

void					irc_help(t_server *server, t_users *user, char **command);
void					irc_nick(t_server *server, t_users *user, char **command);
void					irc_list(t_server *server, t_users *user, char **command);
void					irc_join(t_server *server, t_users *user, char **command);
void					irc_leave(t_server *server, t_users *user, char **command);
void					irc_who(t_server *server, t_users *user, char **command);
void					irc_msg(t_server *server, t_users *user, char **command);
void					irc_topic(t_server *server, t_users *user, char **command);
void					irc_quit(t_server *server, t_users *user, char **command);
void					irc_kill(t_server *server, t_users *user, char **command);

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
void					rpl_whoreply(t_channel *chan, t_users *user, char *nick, char *buf);
void					rpl_endofwho(t_channel *chan, t_users *user, char *buf);
void					rpl_namreply(t_channel *chan, t_users *user, char *nick, char *buf);
void					rpl_endofnames(t_channel *chan, t_users *user, char *buf);
void					rpl_liststart(t_users *user, char *buf);
void					rpl_list(t_channel *channel, t_users *user, char *buf);
void					rpl_endoflist(t_users *user, char *buf);

#endif
