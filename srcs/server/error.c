/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:30:06 by ddinaut           #+#    #+#             */
/*   Updated: 2019/06/04 10:39:20 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_error g_err_ptr[] = {
	invalid_arg,
	invalid_port,
	invalid_socket,
	invalid_bind,
	invalid_listen
};

void	error(int num, const char *err)
{
	int		func_num;

	func_num = sizeof(g_err_ptr) / sizeof(g_err_ptr[0]);
	if (num >= 0 || num < func_num)
		(*g_err_ptr[num])(err);
}
