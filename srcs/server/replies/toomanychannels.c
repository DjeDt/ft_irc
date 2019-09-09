#include "server.h"

void	err_toomanychannels(t_users *user, char *chan_name)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, ERR_TOOMANYCHANNELS, chan_name);
	circular_send(user->socket, buf);
}
