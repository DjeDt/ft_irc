/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:33:12 by ddinaut           #+#    #+#             */
/*   Updated: 2019/06/04 10:38:48 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	invalid_arg(const char *err)
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

void	invalid_listen(const char *err)
{
	fprintf(stderr, "Error: %s. Abort\n", err);
}
