/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:24:36 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 22:56:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool    receive_data(int off, t_data *data)
{
	if (recv(off, data, sizeof(t_data), 0) < 1)
	{
		perror("recv");
		return (false);
	}
	return (true);
}
