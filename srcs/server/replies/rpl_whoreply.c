#include "server.h"

void	rpl_whoreply(t_channel *chan, t_users *user, char *nick, char *buf)
{
	snprintf(buf, MAX_INPUT_LEN, RPL_WHOREPLY, chan->name, nick);
	circular_send(user->socket, buf);
}
