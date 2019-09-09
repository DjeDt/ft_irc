#include "server.h"

void	rpl_endoflist(t_users *user, t_data *data)
{
	data->type = MESSAGE_CODE;
	data->err = false;
	data->len = snprintf(data->data, MAX_INPUT_LEN, RPL_ENDOFLIST);
	send_data_to_single_user(user->socket, data);
}
