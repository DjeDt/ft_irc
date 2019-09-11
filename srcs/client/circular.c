/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 20:36:35 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	search_for_crlf(t_circular *circ, int size)
{
	int	head;

	head = circ->head;
	while (size)
	{
		if (*(unsigned int*)&circ->buf[head] == CRLF_HEX)
			return (true);
		head = (head + 1) % MAX_INPUT_LEN;
		size--;
	}
	return (false);
}

void	circular_push(t_circular *circ, char *received, int size)
{
	int count;

	count = 0;
	while (size)
	{
		circ->buf[circ->tail] = received[count];
		circ->tail = (circ->tail + 1) % MAX_INPUT_LEN;
		size--;
		count++;
	}
}

bool		circular_get(t_interface *inter, t_list_user *user)
{
	int		ret;
	char	data[MAX_INPUT_LEN + 3] = {0};

	ret = recv(user->socket, data, MAX_INPUT_LEN - user->circ.len, 0);
	if (ret < 1)
	{
		refresh_top_interface(inter, "[LOG !] Can't receive data from server\n");
		return (false);
	}
	circular_push(&user->circ, data, ret);
	user->circ.len += ret;
	return (true);
}

void	circular_send(t_interface *inter, t_list_user *user)
{
	if (send(user->socket, user->input, _strlen(user->input), 0) < 0)
	{
		refresh_top_interface(inter, "Can't send data to server.\n");
		return ;
	}
}
