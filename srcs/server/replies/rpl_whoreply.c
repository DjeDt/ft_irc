#include "server.h"

void	rpl_whoreply(t_channel *chan, t_users *user, t_data *data, char *nick)
{
	data->type = MESSAGE_CODE;
	data->err = false;
	data->len = snprintf(data->data, MAX_INPUT_LEN, RPL_WHOREPLY, chan->name, nick);
	send_data_to_single_user(user->socket, data);
}
