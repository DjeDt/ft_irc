#include "client.h"

static bool	manage_client_command(t_interface *inter, t_list_user *user)
{
	int		len;
	bool	ret;
	char	*command[3];

	ret = false;
	ft_memset(command, 0x0, sizeof(char*) * 3);
	if (command_split(command, user->input) != true)
		return (false);
	len = ft_strlen(command[0]);
	if (CONNECT_LEN > len)
		len = CONNECT_LEN;
	if (ft_strncmp(command[0], "/connect", len) == 0)
	{
		wrapper_connect(inter, user, command);
		ret = true;
	}
	command_free(command);
	return (ret);
}

void		interpreter(t_interface *inter, t_list_user *user)
{
	if (user->input[0] == '/')
	{
		if (manage_client_command(inter, user) == true)
			return ;
	}
	if (user->connected == true)
	{
		ft_strncat(user->input, "\r\n", 2);
		circular_send(inter, user);
	}
}
