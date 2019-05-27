#include "server.h"

void	irc_list(t_server *server, char **command, int off)
{
	t_channel	*tmp;
	t_data		data;

	(void)command;
	if (server->chan != NULL)
	{
		tmp = server->chan;
		while (tmp != NULL)
		{
			data.len = sprintf(data.data, "%s: %d users.\n", tmp->name, tmp->num);
			send_data(off, data.data, data.len, 0);
			tmp = tmp->next;
		}
	}
	else
		send_data(off, "No channel here!\n", 17, 0);
}
