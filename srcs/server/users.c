/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:37:45 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/29 14:42:39 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	generate_guest_pseudo(char *pseudo, int id)
{
	char	tmp[10];

	_memset(tmp, 0x0, 10);
	_itoa(tmp, id);
	_memcpy(pseudo, "Guest_", 6);
	_memcpy(&pseudo[6], tmp, 9);
}

t_list_user	*create_new_user(int socket)
{
	t_list_user *new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	_memset(new, 0x0, sizeof(*new));
	new->socket = socket;
	return (new);
}

void	push_new_user(t_list_user **users, t_list_user *chunk)
{
	t_list_user *tmp;

	if (*users == NULL)
		(*users) = chunk;
	else
	{
		tmp = (*users);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = chunk;
	}
	puts("toto");
}

void	add_users(t_list_user **users, int socket)
{
	t_list_user *tmp;

	if (*users == NULL)
		(*users) = create_new_user(socket);
	else
	{
		tmp = (*users);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_new_user(socket);
	}
}

t_list_user		*search_user_by_id(t_list_user *users, int id)
{
	t_list_user *tmp;

	if (users != NULL)
	{
		tmp = users;

		// debug
		printf("TMP user =  %s - socket = %d\n", tmp->nick, tmp->socket);
		while (tmp != NULL)
		{
			if (tmp->socket == id)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

t_list_user		*search_user_by_name(t_list_user *users, const char *name)
{
	int			len;
	t_list_user	*tmp;

	if (users != NULL)
	{
		tmp = users;
		len = _strlen(name);
		while (tmp != NULL)
		{
			if (_memcmp(name, tmp->nick, len) == 0)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void	remove_user(t_list_user **users, int id)
{
	t_list_user *tmp;
	t_list_user *prev;

	prev = NULL;
	tmp = (*users);
	while (tmp != NULL)
	{
		if (tmp->socket == id)
		{
			// debug
			printf("[-] REMOVE user: id=%d, pseudo=%s, status=%d\n", tmp->socket, tmp->nick, tmp->statut);
			if (prev == NULL)
			{
				if (tmp->next != NULL)
					*users = tmp->next;
				else
					*users = NULL;
				free(tmp);
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
