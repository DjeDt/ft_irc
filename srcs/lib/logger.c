/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:17:34 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 21:43:16 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	logger(const char *log, FILE *fd)
{
	char		date[20];
	time_t		now;
    struct tm	*time_ptr;

	now = time(0);
    time_ptr = gmtime(&now);

    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", time_ptr);
	fprintf(fd, "[%s] %s\n", date, log);
}
