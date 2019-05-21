/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_users.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:37:45 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/21 15:37:46 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	generate_guest_pseudo(char *pseudo, int id)
{
	char	tmp[10] = {0};

	// _memset(tmp, 0, 16);
	_itoa(tmp, id);
	_memcpy(pseudo, "Guest_", 6);
	_memcpy(&pseudo[6], tmp, 9);
}

t_users	*create_new_user(int socket)
{
	t_users *new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	_memset(new, 0x0, sizeof(*new));
	new->socket = socket;
	new->statut = GUEST;
	generate_guest_pseudo(new->nick, socket);

	// debug
	printf("[+] ADD user: (id=%d, pseudo=%s, status=%d)\n", new->socket, new->nick, new->statut);
	return (new);
}

void	add_users(t_users **users, int socket)
{
	t_users *tmp;

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

t_users 	*search_user(t_users **users, int id)
{
	t_users *tmp;

	if (*users != NULL)
	{
		tmp = *users;
		while (tmp != NULL)
		{
			if (tmp->socket == id)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void	remove_user(t_users **users, int id)
{
	t_users *tmp;
	t_users *prev;

	prev = NULL;
	tmp = (*users);
	while (tmp != NULL)
	{
		if (tmp->socket == id)
		{
			printf("[-] REMOVE user: id=%d, pseudo=%s, status=%d\n", tmp->socket, tmp->nick, tmp->statut);
			if (prev == NULL)
			{
				if (tmp->next != NULL)
				{
					*users = tmp->next;
					free(tmp);
				}
				else
				{
					free(tmp);
					*users = NULL;
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
