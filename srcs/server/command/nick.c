#include "server.h"

void	irc_nick(t_server *server, char **command, int off)
{
	int			len;
	t_list_user *user;

	if (arrlen(command) > 1)
	{
		len = _strlen(command[1]);
		if (len > MAX_NICK_LEN)
			return ;
		user = search_user(server->users, off);
		if (user != NULL)
		{
			_memset(user->nick, 0x0, MAX_NICK_LEN);
			_memcpy(user->nick, command[1], len);
			send_data(off, "nick set\n", 9, 0);
		}
		printf("[+] NICK set to '%s'\n", user->nick);
		return ;
	}
	printf("[-] NICK failed\n");
}
