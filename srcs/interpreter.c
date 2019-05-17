#include "server.h"

t_error g_func_ptr[] = {
	{ "invalid", invalid_command }
};

void	interpreter(const char *cmd, const char *arg)
{
	int	count;
	int	func_num;

	count = 0;
	func_num = sizeof(g_err_ptr) / sizeof(g_err_ptr[0]);
	if (count <= func_num)
	{
		if (_memcmp(cmd, g_func_ptr.name, sizeof(g_func_ptr.name) == 0)
			(*g_func_ptr[count])(arg);
		return ;
	}
	invalid_command();
}
