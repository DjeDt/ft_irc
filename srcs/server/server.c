/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:20:59 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 19:11:42 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static bool	is_valid_argument(const char *str)
{
	int count;

	count = 0;
	while (str[count] != '\0')
	{
		if (str[count] < '0' || str[count] > '9')
		{
			printf("Error: '%s' port is invalid. Abort\n", str);
			return (false);
		}
		count++;
	}
	return (true);
}

static bool	launcher(t_server *server, char *port)
{
	if (is_valid_argument(port) != true || initialize(server, port) != true)
		return (false);

	if (running(server) != true)
		return (false);

	return (true);
}

void fake_circ_get(char *received, int len, t_circular *circ)
{

	printf("received : %s | %d\n", received, len);
	circular_push(circ, received, len);
//	circ->tail = (circ->tail + len) % MAX_INPUT_LEN;
	circ->len += len;
	printf("[LOG] '%s' | head : %d | tail : %d | len : %d\n", circ->buf, circ->head, circ->tail, circ->len);
}

int			main(int ac, char **av)
{
	t_server server;

	memset(&server, 0x0, sizeof(t_server));

	/* t_circular circ; */
	/* memset(&circ, 0x0, sizeof(t_server)); */
	/* char *command[] = \ */
	/* 	{ */
	/* 		"/join #toto", */
	/* 		"/nick user1", */
	/* 		"salut tout le monde !", */
	/* 	}; */

	/* fake_circ_get(command[0], _strlen(command[0]), &circ); */
	/* circ.len = 0; */
	/* circ.head = circ.tail; */

	/* fake_circ_get(command[1], _strlen(command[1]), &circ); */
	/* circ.len = 0; */
	/* circ.head = circ.tail; */

	/* fake_circ_get(command[2], _strlen(command[2]), &circ); */
	/* circ.len = 0; */
	/* circ.head = circ.tail; */

	/* printf("final : %s\n", circ.buf); */


	/* return (0); */


	if (ac == 1)
	{
		printf("[LOG !] No port provided, using default '%s'\n", DEFAULT_PORT);
		if (launcher(&server, DEFAULT_PORT) != true)
			return (ERROR);
	}
	else if (ac == 2)
	{
		if (launcher(&server, av[1]) != true)
			return (ERROR);
	}
	else
	{
		printf("Usage: %s <port>\n", av[0]);
		return (ERROR);
	}
	return (ERROR);
}
