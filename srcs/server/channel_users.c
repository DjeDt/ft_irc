/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_users.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:09:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:10:29 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_channel_user	*channel_user_create(t_users *user)
{
	t_channel_user *new;

	if (!(new = malloc(sizeof(t_channel_user))))
		return (NULL);
	new->user = user;
	new->next = NULL;
	return (new);
}

t_channel_user	*channel_user_search(t_channel_user *chan, int socket)
{
	t_channel_user *tmp;

	tmp = chan;
	if (tmp != NULL)
	{
		while (tmp != NULL)
		{
			if (tmp->user)
			{
				if (tmp->user->socket == socket)
					return (tmp);
			}
			tmp = tmp->next;
		}
	}
	return (NULL);
}

bool			channel_user_add(t_channel_user **chan, t_users *user)
{
	t_channel_user *tmp;

	if ((*chan) == NULL)
	{
		(*chan) = channel_user_create(user);
		return (true);
	}
	else
	{
		tmp = (*chan);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = channel_user_create(user);
		return (true);
	}
	return (false);
}
