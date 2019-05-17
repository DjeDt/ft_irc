#include "server.h"

void		_itoa(char *pseudo, int n)
{
	int	num;
	int	count;

	num = n;
	count = 1;
	while (n /= 10)
		count++;
	while (count-- > 0)
	{
		pseudo[count] = (num % 10) + '0';
		num /= 10;
	}
}

void	generate_guest_pseudo(char *pseudo, int id)
{
	char	tmp[16] = {0};

	// _memset(tmp, 0, 16);
	_itoa(tmp, id);
	_memcpy(pseudo, "Guest_", 6);
	_memcpy(&pseudo[6], tmp, 9);
}

t_users	*create_new_user(t_single single)
{
	t_users *new;

	new = malloc(sizeof(t_users));
	if (new == NULL)
		return (NULL);
	_memset(new, 0, sizeof(t_users));
	new->fd = single.new;
	new->id = single.new;
	new->statut = GUEST;
	generate_guest_pseudo(new->pseudo, new->id);

	// debug
	printf("[+] ADD user: id=%d, pseudo=%s, status=%d\n", new->id, new->pseudo, new->statut);
	return (new);
}

void	add_users(t_users **users, t_single single)
{
	t_users *tmp;

	if (*users == NULL)
		(*users) = create_new_user(single);
	else
	{
		tmp = (*users);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_new_user(single);
	}
}

void	remove_user(t_users **users, int id)
{
	t_users *tmp;
	t_users *prev;

	prev = NULL;
	tmp = (*users);
	while (tmp != NULL)
	{
		if (tmp->id == id)
		{
			printf("[-] REMOVE user: id=%d, pseudo=%s, status=%d\n", tmp->id, tmp->pseudo, tmp->statut);
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
