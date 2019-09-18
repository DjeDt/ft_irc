/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:11:00 by Dje               #+#    #+#             */
/*   Updated: 2019/09/18 09:11:00 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	uint8_t	*s1;
	uint8_t	*s2;

	i = 0;
	s1 = (uint8_t*)dst;
	s2 = (uint8_t*)src;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (s1);
}
