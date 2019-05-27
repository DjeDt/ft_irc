#include "server.h"

// who <users>
void	irc_who(t_server *server, char **command, int off)
{
	t_list_user *user;

	(void)command;
	if (server->users != NULL)
	{
		user = server->users;
		send_data(off, "Connected users:", 16, 0);
		while (user != NULL)
		{
			send_data(off, user->nick, _strlen(user->nick), 0);
			user = user->next;
		}
	}
	else
	{
		send_data(off, "no one here :(\n", 15, 0);
	}
	printf("WHO\n");
}
