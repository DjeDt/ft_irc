/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:14:34 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/23 18:33:48 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	invalid_arg(const char *err)
{
	fprintf(stderr, "Usage: %s [ip <port>]\n", err);
}

void	invalid_ip(const char *err)
{
	fprintf(stderr, "Error, '%s' is not a valid ip. Abort\n", err);
}

void	invalid_port(const char *err)
{
	fprintf(stderr, "Error, '%s' is not a valid port. Abort\n", err);
}

int		error(enum e_error type, const char *err)
{
	if (type == INVALID_ARG)
		invalid_arg(err);
	else if (type == INVALID_IP)
		invalid_ip(err);
	else if (type == INVALID_PORT)
		invalid_port(err);

	return (ERR);
}
