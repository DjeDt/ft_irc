/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:10:55 by Dje               #+#    #+#             */
/*   Updated: 2019/09/18 09:10:55 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	*ft_memset(void *data, char c, size_t size)
{
	size_t	count;
	uint8_t	*str;

	if (data == NULL)
		return (NULL);
	count = 0;
	str = (uint8_t*)data;
	while (count < size)
		str[count++] = c;
	return (data);
}
