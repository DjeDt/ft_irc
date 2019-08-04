/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:15:40 by ddinaut           #+#    #+#             */
/*   Updated: 2019/08/04 21:53:05 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\n')
		return (0);
	return (1);
}

ssize_t	_strlen(const char *str)
{
	ssize_t count;

	count = 0;
	if (str == NULL)
		return (-1);
	while (str[count] != '\0')
		count++;
	return (count);
}

int		arrlen(char **arr)
{
	int ret;

	ret = 0;
	if (arr == NULL)
		return (0);
	while (arr[ret] != NULL)
		ret++;
	return (ret);
}

void	*_memset(void *data, char c, size_t size)
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

void	*_memcpy(void *dst, void *src, size_t n)
{
	uint8_t	*s1;
	uint8_t	*s2;
	size_t	i;

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

int		_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
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

char	*_strchr(const char *s, char c)
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

void		_itoa(char *str, int n)
{
	int	num;
	int	count;

	num = n;
	count = 1;
	while (n /= 10)
		count++;
	while (count-- > 0)
	{
		str[count] = (num % 10) + '0';
		num /= 10;
	}
}

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
