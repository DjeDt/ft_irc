#include "server.h"

t_users	*user_search_by_id(t_users *users, int id)
{
	t_users *tmp;

	if (users != NULL)
	{
		tmp = users;
		while (tmp != NULL)
		{
			if (tmp->socket == id)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

t_users	*user_search_by_name(t_users *users, const char *name)
{
	int		len;
	t_users	*tmp;

	if (users != NULL)
	{
		tmp = users;
		len = ft_strlen(name);
		while (tmp != NULL)
		{
			if (ft_memcmp(name, tmp->nick.nick, len) == 0)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}
