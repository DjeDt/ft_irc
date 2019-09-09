#include "server.h"

void	rpl_endofwho(t_channel *chan, t_users *user, char *buf)
{
	snprintf(buf, MAX_INPUT_LEN, RPL_ENDOFWHO, chan->name);
	circular_send(user->socket, buf);
}
