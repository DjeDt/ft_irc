#include "server.h"

void	rpl_list(t_channel *channel, t_users *user, char *buf)
{
	snprintf(buf, MAX_INPUT_LEN, RPL_LIST, channel->name, channel->num);
	circular_send(user->socket, buf);
}
