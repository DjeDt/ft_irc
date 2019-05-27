#include "server.h"

void	irc_leave(t_server *server, char **command, int off)
{
	t_channel *chan;

	chan = search_channel(server->chan, command[1]);
	if (chan == NULL)
	{
		send_data(off, "this channel doesn't exist.\n", 29, 0);
		return ;
	}
	else if (FD_ISSET(off, &chan->connected))
	{
		chan->num -= 1;
		if (chan->num == 0)
			delete_channel(&server->chan, chan->name);
		FD_CLR(off, &chan->connected);
		send_data(off, "Disconnected.\n", 14, 0);
	}
	else
		send_data(off, "you are not connected to this channel.\n", 40, 0);
}
