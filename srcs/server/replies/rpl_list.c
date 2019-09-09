#include "server.h"

void	rpl_list(t_channel *channel, t_users *user, t_data *data)
{
	data->type = MESSAGE_CODE;
	data->err = false;
	data->len = snprintf(data->data, MAX_INPUT_LEN, RPL_LIST, channel->name, channel->num);
	send_data_to_single_user(user->socket, data);
}
