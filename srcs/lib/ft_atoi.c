/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:11:09 by Dje               #+#    #+#             */
/*   Updated: 2019/09/18 09:11:10 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	delim(char c)
{
	if (c == '\t' || c == '\v' || c == '\n'
		|| c == '\r' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	char	n;
	int		i;
	int		nbr;

	nbr = 0;
	n = 0;
	i = 0;
	while (delim(str[i]))
		i++;
	if (str[i] == '-')
		n = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] > 47) && (str[i] < 58))
	{
		nbr = (nbr * 10) + str[i] - 48;
		i++;
	}
	if (n == 1)
		return (-nbr);
	return (nbr);
}
