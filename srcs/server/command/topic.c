#include "server.h"

static void	err_topictoolong(t_users *user, char *topic)
{
	int		len;
	char	buf[MAX_INPUT_LEN + 3];

	len = snprintf(buf, MAX_INPUT_LEN + 3, "[server]: <%s> :Topic too long.%s", topic, CRLF);
	circular_send(user->socket, buf, len);
}

static void	send_channel_topic(t_channel *chan, t_users *user)
{
	if (chan->topic == NULL)
		rpl_notopic(chan, user);
	else
		rpl_topic(chan, user);
}

static void	modify_channel_topic(t_channel *chan, t_users *user, char *new_topic)
{
	int	size;

	size = _strlen(new_topic);
	if (size > MAX_TOPIC_LEN)
	{
		err_topictoolong(user, new_topic);
		return ;
	}
	if (chan->topic != NULL)
		free(chan->topic);
	chan->topic = malloc(size + 1);
	memset(chan->topic, 0x0, size + 1);
	memcpy(chan->topic, new_topic, size);
}

void	irc_topic(t_server *server, t_users *user, char **command)
{
	t_channel *chan;

	if (command[1] != NULL)
	{
		chan = channel_search(&server->channel, command[1]);
		if (chan == NULL)
		{
			err_nosuchchannel(user, command[1]);
			return ;
		}
		if (command[2] == NULL)
			send_channel_topic(chan, user);
		else
			modify_channel_topic(chan, user, command[2]);
		return ;
	}
	err_needmoreparams(user, command[0]);
}
