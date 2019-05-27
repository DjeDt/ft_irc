#include "server.h"

t_channel	*create_channel(char *name)
{
	t_channel *new;

	if (!(new = malloc(sizeof(t_channel))))
		return (NULL);
	new->num = 0;
	FD_ZERO(&new->connected);
	_memset(new->name, 0x0, MAX_CHAN_LEN);
	_memcpy(new->name, name, _strlen(name));
	new->next = NULL;

	// debug
	printf("[+] CHANNEL create '%s'\n", new->name);
	return (new);
}

t_channel	*add_channel(t_channel **chan, char *name)
{
	t_channel *tmp;

	if (*chan == NULL)
	{
		*chan = create_channel(name);
		return (*chan);
	}
	tmp = (*chan);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_channel(name);
	return (tmp->next);
}

t_channel	*search_channel(t_channel *chan, char *name)
{
	int			len;
	t_channel	*ret;

	ret = chan;
	len = _strlen(name);
	while (ret != NULL)
	{
		if (_memcmp(ret->name, name, len) == 0)
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

void	delete_channel(t_channel **channel, char *name)
{
	int			len;
	t_channel	*tmp;
	t_channel	*prev;

	prev = NULL;
	len = _strlen(name);
	tmp = (*channel);
	while (tmp != NULL)
	{
		if (_memcmp(tmp->name, name, len) == 0)
		{
			// debug
			printf("[-] REMOVE channel '%s'\n", tmp->name);

			if (prev == NULL)
			{
				if (tmp->next != NULL)
				{
					*channel = tmp->next;
					free(tmp);
				}
				else
				{
					free(tmp);
					*channel = NULL;
				}
			}
			else
			{
				prev->next = tmp->next;
				free(tmp);
			}
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
