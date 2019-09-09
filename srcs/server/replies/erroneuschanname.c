#include "server.h"

void	err_erroneuschanname(t_users *user, char *name)
{
	char buf[MAX_INPUT_LEN + 3];

	snprintf(buf, MAX_INPUT_LEN, ERR_ERRONEUSCHANNAME, name);
	circular_send(user->socket, buf);
}
