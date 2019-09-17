#include "client.h"

static void	manage_local_command(t_interface *inter, t_list_user *user, char **command)
{
	int len;

	len = ft_strlen(command[0]);
	if (ft_strncmp(command[0], "/connect", len > CONNECT_LEN ? len : CONNECT_LEN) == 0)
	{
		wrapper_connect(inter, user, command);
		return ;
	}
	else if (ft_strncmp(command[0], "/quit", len > QUIT_LEN ? len : QUIT_LEN) == 0)
	{
		user->connected = false;
		FD_CLR(user->socket, &user->client.master);
		close(user->socket);
		ft_strncat(user->input, "\r\n", 2);
		circular_send(inter, user);
		stop_interface(inter);
		exit(SUCCESS);
	}
	ft_strncat(user->input, "\r\n", 2);
	circular_send(inter, user);
}

void		interpreter(t_interface *inter, t_list_user *user)
{
	char	*command[3];

	if (user->input[0] == '/')
	{
		memset(command, 0x0, sizeof(char*) * 3);
		if (command_split(command, user->input) == false)
			return ;
		manage_local_command(inter, user, command);
		command_free(command);
		return ;
	}
	else if (user->connected == true)
	{
		ft_strncat(user->input, "\r\n", 2);
		circular_send(inter, user);
	}
}
