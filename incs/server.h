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

// DEBUG
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

/*
** Typedef
*/
typedef void	(*t_error) (const char *err);

typedef struct s_client
{
	fd_set		master;
	fd_set		backup;
	int			fd_max;
}				t_client;

typedef struct	s_server
{
	int			port;
	int			socket;
}				t_server;

/*
** Functions
*/

/* core */
bool			initialize(t_server *server, const char *str);
bool			running(t_server *server);

/* lib */
ssize_t			_strlen(const char *str);
void			*_memset(void *data, char c, size_t size);
void			logger(const char *log, FILE *fd);

/* error handler */
void			error(int num, const char *err);
void			missing_arg(const char *str);
void			invalid_port(const char *str);
void			invalid_socket(const char *str);
void			invalid_bind(const char *err);

#endif
