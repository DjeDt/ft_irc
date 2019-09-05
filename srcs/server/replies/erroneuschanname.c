#include "server.h"

void	err_erroneuschanname(t_users *user, char *name)
{
	t_data data;

	data.type = ERROR_CODE;
	data.err = ERR_ERRONEUSCHANNAME_ID;
	data.len = snprintf(data.data, MAX_INPUT_LEN, "[server]: <%s> :Erroneus chan name.", name);
	send_data_to_single_user(user->socket, &data);
}
