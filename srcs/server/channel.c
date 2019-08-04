/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 09:39:16 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 20:51:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_channel	*channel_create(char *name)
{
	int			len;
	t_channel	*new;

	puts("Create channel");
	if (!(new = malloc(sizeof(t_channel))))
		return (NULL);
	_memset(new, 0x0, sizeof(*new));
 	len = _strlen(name);
	if (len > MAX_NICK_LEN)
		_memcpy(new->name, name, MAX_NICK_LEN);
	else
		_memcpy(new->name, name, len);
	new->next = NULL;

	// debug
	printf("[+] channel created '%s'\n", new->name);
	return (new);
}

t_channel	*channel_add(t_channel **chan, char *name)
{
	t_channel *tmp;

	puts("Add channel");
	if (*chan == NULL)
	{
		*chan = channel_create(name);
		return (*chan);
	}
	else
	{
		tmp = (*chan);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = channel_create(name);
		return (tmp->next);
	}
	return (NULL);
}

t_channel	*channel_search(t_channel *chan, char *name)
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

void	channel_delete(t_channel **channel, char *name)
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
			printf("[-] remove channel '%s'\n", tmp->name);
			if (prev == NULL)
			{
				if (tmp->next != NULL)
				{
					puts("ret1");
					*channel = tmp->next;
					free(tmp);
					return ;
				}
				else
				{
					puts("ret2");
					free(tmp);
					*channel = NULL;
					return ;
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
