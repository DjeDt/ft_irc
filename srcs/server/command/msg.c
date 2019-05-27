#include "server.h"

// msg <nickname> <message>
void	irc_msg(t_server *server, char **command, int off)
{
	send_data(off, "todo\n", 5, 0);
	(void)server;
	(void)command;
	(void)off;
	printf("[%s] MSG\n", command[0]);
}
