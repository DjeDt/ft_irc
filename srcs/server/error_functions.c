#include "server.h"

void	missing_arg(const char *err)
{
	fprintf(stderr, "[%s] Usage:\n\t./server <port>\n", err);
	return ;
}

void	invalid_port(const char *err)
{
	fprintf(stderr, "Error: '%s' port is invalid. Abort\n", err);
	return ;
}

void	invalid_socket(const char *err)
{
	fprintf(stderr, "Error: %s. Abort\n", err);
	return ;
}

void	invalid_bind(const char *err)
{
	fprintf(stderr, "Error: %s. Abort\n", err);
	return ;
}
