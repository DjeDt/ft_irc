#include "server.h"

// client side
void	irc_connect(t_server *server, char **command, int off)
{
	(void)server;
	(void)command;
	(void)off;
	printf("[%s] CONNECT\n", command[0]);
}
