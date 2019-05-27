#include "server.h"

void	irc_quit(t_server *server, char **command, int off)
{
	if (server->users != NULL)
	{
		remove_user(&server->users, off);
		close(off);
		FD_CLR(off, &server->client.master);
		printf("[-] [%s] CLOSED connection for %d\n", command[0], off);
	}
	printf("[%s] QUIT\n", command[0]);
}
