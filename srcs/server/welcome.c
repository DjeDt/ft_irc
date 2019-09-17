#include "server.h"

void	send_welcome(t_users *user)
{
	int		len;
	char	data[MAX_INPUT_LEN + 3];

	len = snprintf(data, MAX_INPUT_LEN + 3, \
		"Welcome '%s' !\n Please use /join or /help to get started!\r\n", \
		user->nick.nick);
	circular_send(user->socket, data, len);
}
