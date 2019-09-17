/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:37:45 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:12:54 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	generate_guest_pseudo(char *pseudo, int id)
{
	char tmp[10];

	ft_memset(tmp, 0x0, 10);
	ft_itoa(tmp, id);
	ft_memcpy(pseudo, "Guest_", 6);
	ft_memcpy(&pseudo[6], tmp, 9);
}

t_users	*user_create(int socket)
{
	t_users *new;

	if ((new = malloc(sizeof(t_users))) == NULL)
		return (NULL);
	new->socket = socket;
	ft_memset(&new->nick, 0x0, sizeof(t_nick));
	generate_guest_pseudo(new->nick.nick, socket);
	new->nick.nick_len = ft_strlen(new->nick.nick);
	new->circ.len = 0;
	new->circ.head = 0;
	new->circ.tail = 0;
	ft_memset(new->circ.buf, 0x0, MAX_INPUT_LEN);
	new->chan = NULL;
	new->next = NULL;
	return (new);
}

void	user_push(t_users **users, t_users *chunk)
{
	t_users *tmp;

	if (*users == NULL)
		(*users) = chunk;
	else
	{
		tmp = (*users);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = chunk;
	}
}

void	user_add(t_users **users, int socket)
{
	t_users *tmp;

	if (*users == NULL)
		(*users) = user_create(socket);
	else
	{
		tmp = (*users);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = user_create(socket);
	}
}

void	user_remove(t_users **users, int id)
{
	t_users *tmp;
	t_users *prev;

	prev = NULL;
	tmp = (*users);
	while (tmp != NULL)
	{
		if (tmp->socket == id)
		{
			if (prev == NULL)
				(*users) = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
