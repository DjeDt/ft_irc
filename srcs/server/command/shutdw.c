#include "server.h"

// close the server
void	irc_shutdown(t_server *server, char **command, int off)
{
	(void)server;
	(void)command;
	(void)off;
	printf("[%s] SHUTDOWN\n", command[0]);
}
