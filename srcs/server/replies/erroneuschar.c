/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroneuschar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:10:06 by Dje               #+#    #+#             */
/*   Updated: 2019/09/18 09:10:08 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	err_erroneuschar(t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + 3];

	len = snprintf(buf, MAX_INPUT_LEN + 3, ERR_ERRONEUSCHAR);
	circular_send(user->socket, buf, len);
}
