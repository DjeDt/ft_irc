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
	t_channel	*new_chan;

	if (!(new_chan = malloc(sizeof(t_channel))))
		return (NULL);

	memset(new_chan, 0x0, sizeof(t_channel));
 	len = _strlen(name);
	if (len > MAX_CHAN_LEN)
		len = MAX_CHAN_LEN;

	new_chan->num = 0;
	_memcpy(new_chan->name, name, len);

	new_chan->name_len = len;
	new_chan->users = NULL;
	new_chan->next = NULL;



	printf("SDKFHGLSKJFDGH ==== %lu\n", sizeof(t_channel));
	printf("[+] channel created '%s'\n", new_chan->name);
	printf("===== addr chan = %p\n", &new_chan);
	return (new_chan);
}

t_channel	*channel_add(t_channel **chan, char *name)
{
	t_channel *tmp;

	if ((*chan) == NULL)
	{
		(*chan) = channel_create(name);
		tmp = (*chan);
		return (tmp);
	}
	else
	{
		tmp = (*chan);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = channel_create(name);
		return (tmp->next);
	}
}

t_channel	*channel_search(t_channel *chan, char *name)
{
	int			len;
	t_channel	*ret;

	ret = chan;
	len = _strlen(name);
	while (ret != NULL)
	{
		if (len > ret->name_len)
		{
			if (_memcmp(ret->name, name, len) == 0)
				return (ret);
		}
		else
		{
			if (_memcmp(ret->name, name, _strlen(chan->name)) == 0)
				return (ret);
		}
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
		if (_memcmp(tmp->name, name, len > tmp->name_len ? len : tmp->name_len) == 0)
		{

			printf("[-] REMOVE channel '%s'\n", tmp->name);

			/* if (tmp->users != NULL) */
			/* 	channel_user_remove_all(&tmp->users); */

			if (prev == NULL)
				(*channel) = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
