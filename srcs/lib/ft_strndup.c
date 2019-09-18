/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:10:38 by Dje               #+#    #+#             */
/*   Updated: 2019/09/18 09:10:39 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	count;
	char	*ret;

	count = 0;
	if (ft_strlen(src) < (ssize_t)n)
		n = ft_strlen(src);
	ret = malloc(sizeof(char) * n + 1);
	if (!ret)
		return (NULL);
	ft_memset(ret, 0, n + 1);
	while (src[count] != '\0' && count < n)
	{
		ret[count] = src[count];
		count++;
	}
	return (ret);
}
