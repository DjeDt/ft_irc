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
# define MAX_PSEUDO_LEN	16
# define MAX_INPUT_LEN	512

# define GUEST			0
# define LOGGED			1

/*
** Typedef
*/
typedef void	(*t_error) (const char *err);

typedef struct			s_single
{
	int					new;
	socklen_t			len;
	struct sockaddr_in	addr;
}						t_single;

typedef struct			s_users
{
	int					fd;
	int					id;
	int					statut;
	char				pseudo[MAX_PSEUDO_LEN];
	struct s_users		*next;
}						t_users;

typedef struct			s_client
{
	fd_set				master;
	fd_set				backup;
	int					fd_max;
	t_single			single;
}						t_client;

typedef struct			s_server
{
	int					port;
	int					socket;
}						t_server;

/*
** Functions
*/

/* core */
bool					initialize(t_server *server, const char *str);
bool					running(t_server *server);

bool					receive_data(t_server *server, t_client *client, int count);
bool					send_data(int fd, char *data, int size, int flag);

void					add_users(t_users **users, t_single single);
void					remove_user(t_users **users, int id);

/* lib */
ssize_t					_strlen(const char *str);
char					*_strchr(const char *str, char c);
void					*_memset(void *data, char c, size_t size);
void					*_memcpy(void *dst, void *src, size_t n);
void					logger(const char *log, FILE *fd);

/* error handler */
void					error(int num, const char *err);
void					missing_arg(const char *str);
void					invalid_port(const char *str);
void					invalid_socket(const char *str);
void					invalid_bind(const char *err);

#endif
