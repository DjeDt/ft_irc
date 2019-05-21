/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _strsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:03:26 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/20 17:12:58 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*_strndup(const char *src, size_t n)
{
	size_t	count;
	char	*ret;


	count = 0;
	if (_strlen(src) < (ssize_t)n)
		n = _strlen(src);
	ret = malloc(sizeof(char) * n + 1);
	if (!ret)
		return (NULL);
	_memset(ret, 0, n + 1);
	while (src[count] != '\0' && count < n)
	{
		ret[count] = src[count];
		count++;
	}
	return (ret);
}

static int	found_one(char c, const char *delim)
{
	int i;

	i = 0;
	if (c == 0)
		return (0);
	while (delim[i] != '\0')
	{
		if (delim[i] == c)
			return (0);
		i++;
	}
	return (-1);
}

static int	count_word(const char *str, const char *delim)
{
	int	i;
	int count;

	i = -1;
	count = 0;
	while (str[++i] != '\0')
	{
		if ((found_one(str[i], delim) == -1) && \
			(found_one(str[i + 1], delim) == 0))
			count++;
	}
	return (count);
}

char		**_strtok(const char *str, const char *delim)
{
	int		j;
	int		k;
	int		count;
	char	**tab;

	if (str == NULL)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * (count_word(str, delim) + 1))))
		return (NULL);
	j = -1;
	k = 0;
	count = -1;
	while (str[++count] != '\0')
	{
		found_one(str[count], delim) == -1 ? k++ : 0;
		if ((found_one(str[count], delim) == -1) && \
			(found_one(str[count + 1], delim) == 0))
		{
			tab[++j] = _strndup(&str[count - (k - 1)], k);
			k = 0;
		}
	}
	tab[++j] = NULL;
	return (tab);
}
