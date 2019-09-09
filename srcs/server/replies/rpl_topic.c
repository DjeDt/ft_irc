#include "server.h"

void	rpl_topic(t_channel *channel, t_users *user)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, RPL_TOPIC, channel->name, channel->topic);
	circular_send(user->socket, buf);
}
