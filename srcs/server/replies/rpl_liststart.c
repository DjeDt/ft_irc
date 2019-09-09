#include "server.h"

void	rpl_liststart(t_users *user, char *buf)
{
	snprintf(buf, MAX_INPUT_LEN, RPL_LISTSTART);
	circular_send(user->socket, buf);
}
