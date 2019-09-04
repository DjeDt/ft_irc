#include "server.h"

void	err_toomanychannels(t_users *user, char *chan_name)
{
	t_data data;

	data.type = ERROR_CODE;
	data.err = ERR_TOOMANYCHANNELS_ID;
	data.len = snprintf(data.data, MAX_INPUT_LEN, "<%s> : :You have joined too many channels", chan_name);
	send_data_to_single_user(user->socket, &data);
}
