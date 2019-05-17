#include "server.h"

// TODO
bool	init_socket_ipv6(t_server *server, struct sockaddr_in addr)
{
	server->socket = socket(PF_INET6, SOCK_STREAM, 0);
	if (server->socket < 0)
	{
		error(INVALID_SCKT, "can't create socket using ipv6");
		return (false);
	}
	addr.sin_family = AF_INET6;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(server->port);
	if (bind(server->socket, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0)
	{
		error(INVALID_BIND, "can't bind socket to address using ipv6");
		return (false);
	}
	logger("socket correctly setup using ipv6", stderr);
	return (false);
}

static bool	init_socket_ipv4(t_server *server, struct sockaddr_in addr)
{
	server->socket = socket(PF_INET, SOCK_STREAM, 0);
	if (server->socket < 0)
	{
		error(INVALID_SCKT, "can't create socket using ipv4");
		return (false);
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(server->port);
	if (bind(server->socket, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0)
	{
		error(INVALID_BIND, "can't bind socket to address using ipv4");
		return (false);
	}
	logger("socket correctly setup using ipv4", stderr);
	return (true);
}

bool	initialize(t_server *server, const char *port)
{
	socklen_t			len;
	struct sockaddr_in	addr;

	_memset(server, 0, sizeof(*server));
	server->port = atoi(port);
	len = sizeof(addr);
	_memset(&addr, 0, len);
	if (server->port < 1)
	{
		error(INVALID_PORT, port);
		return (false);
	}
	if (init_socket_ipv4(server, addr) != true)
		return (false);

	if (listen(server->socket, MAX_QUEUE) < 0)
	{
		perror("listen");
		return (false);
	}
	return (true);
}
