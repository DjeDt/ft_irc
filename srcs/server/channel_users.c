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

void			print_channel_user(t_channel_user *chan)
{
	t_channel_user *tmp;

	tmp = chan;
	while (tmp != NULL)
	{
		printf("\tuser : %s\n", tmp->user->nick.nick);
		tmp = tmp->next;
	}
}

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

bool			channel_user_remove(t_channel_user **chan, t_users *user)
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
				printf("[LOG -] Remove user '%s'\n", curr->user->nick.nick);
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

void			channel_user_remove_all(t_channel_user **user_list)
{
	t_channel_user *tmp;
	t_channel_user *tmp2;

	tmp = (*user_list);
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		memset(tmp, 0x0, sizeof(t_channel_user));
		free(tmp);
		tmp = tmp2;
	}
	free(*user_list);
	(*user_list) = NULL;
}

void			channel_user_remove_full(t_channel **channel, t_users *user)
{
	t_channel *tmp;

	tmp = (*channel);
	while (tmp != NULL)
	{
		channel_user_remove(&tmp->users, user);
		tmp = tmp-> next;
	}
}
