/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:10:53 by Dje               #+#    #+#             */
/*   Updated: 2019/09/18 09:10:53 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strchr(const char *s, char c)
{
	int		i;
	char	*ret;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == c)
			{
				ret = (char*)&s[i];
				return (ret);
			}
			i++;
		}
		if (s[i] == c)
			return ((char*)&s[i]);
	}
	return (NULL);
}
