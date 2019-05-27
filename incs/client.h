/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:16:13 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/24 11:29:31 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

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

enum	e_error
{
	INVALID_ARG,
	INVALID_PORT,
	INVALID_IP
};


/*
** Defines
*/

# define MAX_QUEUE		5
# define MAX_NICK_LEN	16
# define MAX_INPUT_LEN	512

# define GUEST			0
# define LOGGED			1

/* Error/Success */
# define ERR			-1
# define SCS			0

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

typedef struct			s_users
{
	int					socket;		// also used as an id
	int					statut;		// loged or not
	t_client			client;
	char				nick[MAX_NICK_LEN];
}						t_users;

/*
** Functions
*/

/* core */
void					running(t_users *user);
void					interpreter(t_users *user, t_data data);


bool					receive_data(t_users *user, int off);
bool					receive_full(int off, t_data *data, size_t size, int flag);
/* Builtin */
bool					connect_to_server(t_users *client, const char *ip, const char *port);


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

/* Error */
int						error(enum e_error type, const char *err);


#endif
