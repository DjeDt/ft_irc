/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_users_remove.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:09:00 by Dje               #+#    #+#             */
/*   Updated: 2019/10/01 15:57:06 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool	channel_user_remove(t_channel_user **users, t_users *user)
{
	t_channel_user	*curr;
	t_channel_user	*prev;

	prev = NULL;
	curr = (*users);
	while (curr != NULL)
	{
		if ((curr->user != NULL) && (curr->user->socket == user->socket))
		{
			printf("[LOG -] Remove user '%s' from chan '%s\n", \
				curr->user->nick.nick, ((t_channel*)curr->user->chan)->name);
			if (prev == NULL)
				(*users) = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			return (true);
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
