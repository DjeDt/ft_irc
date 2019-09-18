/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:11:21 by Dje               #+#    #+#             */
/*   Updated: 2019/09/18 09:11:21 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	uint8_t	*str1;
	uint8_t	*str2;

	i = 0;
	str1 = (uint8_t*)s1;
	str2 = (uint8_t*)s2;
	while (n--)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
