#include "server.h"

void	err_erroneuschar(t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + 3];

	len = snprintf(buf, MAX_INPUT_LEN + 3, ERR_ERRONEUSCHAR);
	circular_send(user->socket, buf, len);
}
