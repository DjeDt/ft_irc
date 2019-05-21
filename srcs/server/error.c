#include "server.h"

t_error g_err_ptr[] = {
	missing_arg,
	invalid_port,
	invalid_socket,
	invalid_bind
};

void	error(int num, const char *err)
{
	int		func_num;

	func_num = sizeof(g_err_ptr) / sizeof(g_err_ptr[0]);
	if (num >= 0 || num < func_num)
		(*g_err_ptr[num])(err);
}
