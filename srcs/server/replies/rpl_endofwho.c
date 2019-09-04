#include "server.h"

void	rpl_endofwho(t_channel *chan, t_users *user, t_data *data)
{
	data->type = MESSAGE_CODE;
	data->err = false;
	data->len = snprintf(data->data, MAX_INPUT_LEN, "[%s]: end of /who list.", chan->name);
	send_data_to_single_user(user->socket, data);
}
