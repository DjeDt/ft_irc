/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:06:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/19 18:13:07 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool	search_for_crlf(char *buf, int head, int size)
{
	int next;

	while (size)
	{
		next = (head + 1) % MAX_INPUT_LEN;
		if (buf[head] == 0xd && buf[next] == 0xa)
			return (true);
		head = next;
		size--;
	}
	return (false);
}

void	circular_push(t_circular *circ, char *received, int size)
{
	while (size)
	{
		circ->buf[circ->tail] = *received++;
		circ->tail = (circ->tail + 1) % MAX_INPUT_LEN;
		size--;
	}
}

void	extract_and_update(t_circular *circ, char *final)
{
	int count;
	int next;

	count = 0;
	while (count < circ->len)
	{
		next = (circ->head + 1) % MAX_INPUT_LEN;
		if (circ->buf[circ->head] == 0xd && circ->buf[next] == 0xa)
		{
			circ->head = (circ->head + 2) % MAX_INPUT_LEN;
			circ->len -= (count + 2);
			break ;
		}
		final[count] = circ->buf[circ->head];
		circ->head = next;
		count++;
	}
	final[count] = '\0';
}

bool	circular_get(t_users *user)
{
	int				ret;
	char			data[MAX_INPUT_LEN + CRLF];
	unsigned char	decrypted[MAX_INPUT_LEN + CRLF];

	ft_memset(data, 0x0, sizeof(data));
	ft_memset(decrypted, 0x0, sizeof(decrypted));
	ret = recv(user->socket, data, (MAX_INPUT_LEN + CRLF) - user->circ.len, 0);

	if (ret < 1)
	{
		printf("[LOG !] Can't receive data from [%d]\n", user->socket);
		return (false);
	}

    printf(" encrypted : ");
	for (int i = 0 ; i < ret ; i++)
		printf("%x ", (uint8_t)data[i]);
	printf("\n");

	rc4(SECRET_KEY, data, decrypted);

    printf("decrypted : ");
	for (int i = 0 ; i < ret ; i++)
		printf("%x ", decrypted[i]);
	printf("\n");

	circular_push(&user->circ, (char*)decrypted, ret);
	user->circ.len += ret;
	return (true);
}

void	circular_send(int socket, char *data, int size)
{
	unsigned char encrypted[MAX_INPUT_LEN + CRLF];

	rc4(SECRET_KEY, data, encrypted);
	if (send(socket, encrypted, size, 0) < 0)
	{
		printf("[LOG !] Can't send data to %d\n", socket);
		return ;
	}
	else
		printf("Sent to %d : '%s'", socket, data);
}
