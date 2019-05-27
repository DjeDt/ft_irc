#include "server.h"

void	irc_join(t_server *server, char **command, int off)
{
	t_channel *chan;

	chan = search_channel(server->chan, command[1]);
	if (chan == NULL)
	{
		if ((chan = add_channel(&server->chan, command[1])) == NULL)
			return ;
		chan->num += 1;
		FD_SET(off, &chan->connected);
		send_data(off, "Joined!\n", 8, 0);
	}
	else if (!FD_ISSET(off, &chan->connected))
	{
		chan->num += 1;
		FD_SET(off, &chan->connected);
		send_data(off, "Joined!\n", 8, 0);
	}
	else
		send_data(off, "Error, you have already joined this channel.\n", 46, 0);
}
