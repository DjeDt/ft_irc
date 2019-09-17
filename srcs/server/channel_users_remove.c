#include "server.h"

bool	channel_user_remove(t_channel_user **chan, t_users *user)
{
	t_channel_user *curr;
	t_channel_user *prev;

	prev = NULL;
	curr = (*chan);
	while (curr != NULL)
	{
		if (curr->user != NULL)
		{
			if (curr->user->socket == user->socket)
			{
				printf("[LOG -] Remove user '%s' from chan '%s\n", \
				curr->user->nick.nick, ((t_channel*)curr->user->chan)->name);
				if (prev == NULL)
					(*chan) = curr->next;
				else
					prev->next = curr->next;
				free(curr);
				return (true);
			}
		}
		prev = curr;
		curr = curr->next;
	}
	return (false);
}

void	channel_user_remove_all(t_channel_user **user_list)
{
	t_channel_user *tmp;
	t_channel_user *tmp2;

	tmp = (*user_list);
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		ft_memset(tmp, 0x0, sizeof(t_channel_user));
		free(tmp);
		tmp = tmp2;
	}
	free(*user_list);
	(*user_list) = NULL;
}

void	channel_user_remove_full(t_channel **channel, t_users *user)
{
	t_channel *tmp;

	tmp = (*channel);
	while (tmp != NULL)
	{
		channel_user_remove(&tmp->users, user);
		tmp = tmp->next;
	}
}
