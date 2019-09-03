/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:30:06 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 16:08:49 by ddinaut          ###   ########.fr       */
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

void	error(int ref, const char *err)
{
	int		func_num;

  	func_num = sizeof(g_err_ptr) / sizeof(g_err_ptr[0]);
	if (ref >= 0 || ref < func_num)
		(*g_err_ptr[ref])(err);
}
