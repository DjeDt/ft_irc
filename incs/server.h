/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:19:18 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/26 22:13:44 by ddinaut          ###   ########.fr       */
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

typedef struct			s_user
{
	int					socket;
	int					statut;
	char				nick[MAX_NICK_LEN];
	struct sockaddr_in	addr;
}						t_user;

typedef struct			s_btree
{
	t_user				data;
	struct s_btree		*root;
	struct s_btree		*left;
	struct s_btree		*right;
}						t_btree;

typedef struct			s_server
{
	int					port;
	int					socket;
	t_client			client;
	t_btree				*users;
}						t_server;

typedef void (*t_error) (const char *err);
typedef void (t_func) (t_server *server, char **command, int off);

/*
** Functions
*/

/* core */
bool					initialize(t_server *server, const char *str);
bool					running(t_server *server);
bool					interpreter();

bool					receive_data(t_server *server, t_data *data, int off);

bool					send_to_all(t_server *server, t_client *client, t_data data, int count);
bool					send_data(int fd, char *data, int size, int flag);

/* void					add_users(t_users **users, int socket); */
/* void					remove_user(t_users **users, int id); */
/* t_users					*search_user(t_users **users, int id); */

/* lib */
ssize_t					_strlen(const char *str);
int						arrlen(char **arr);
char					*_strchr(const char *str, char c);
void					*_memset(void *data, char c, size_t size);
void					*_memcpy(void *dst, void *src, size_t n);
void					logger(const char *log, FILE *fd);
char					**_strtok(const char *str, const char *delim);
int						_memcmp(const void *s1, const void *s2, size_t n);
int		intcmp(int x, int y);
void					_itoa(char *str, int n);

/* tree */
int						btree_find_min(t_btree *node);
void					btree_delete_node_int(t_btree **root, int key);
t_btree					*btree_create_node(t_user data);
void					btree_insert_data_int(t_btree **root, t_user data, int (*func)(int, int));
void					btree_insert_data_char(t_btree **root, t_user data, int (*func)(char*, char*));
t_btree					*btree_search_item_int(t_btree *root, int ref, int (*func)(int, int));
t_btree					*btree_search_item_char(t_btree *root, char *ref, int (*func)(char *, char *));



/* error handler */
void					error(int num, const char *err);
void					missing_arg(const char *str);
void					invalid_port(const char *str);
void					invalid_socket(const char *str);
void					invalid_bind(const char *err);

#endif
