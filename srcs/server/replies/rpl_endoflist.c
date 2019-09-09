#include "server.h"

void	rpl_endoflist(t_users *user, char *buf)
{
	snprintf(buf, MAX_INPUT_LEN, RPL_ENDOFLIST);
	circular_send(user->socket, buf);
}
