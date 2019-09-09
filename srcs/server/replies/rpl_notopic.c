#include "server.h"

void	rpl_notopic(t_channel *channel, t_users *user)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, RPL_NOTOPIC, channel->name);
	circular_send(user->socket, buf);
}
