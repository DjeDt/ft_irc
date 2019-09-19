/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:06:15 by Dje               #+#    #+#             */
/*   Updated: 2019/09/19 18:10:17 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	swap(unsigned char *x, unsigned char *y)
{
	int tmp;

	tmp = (*x);
	(*x) = (*y);
	(*y) = tmp;
}

static void	permutation(char *key, unsigned char *S)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < N)
	{
		S[i] = i;
		i++;
	}

	i = 0;
	while (i < N)
	{
		j = (j + S[i] + key[i % KEY_LEN]) % N;
		swap(&S[i], &S[j]);
		i++;
	}
}

static void	generate(unsigned char *S, char *plain, int size, unsigned char *cypher)
{
	int i;
	int j;
	int cyph;
	int count;
	int flag;

	i = 0;
	j = 0;
	count = 0;
	flag = false;
	while (count < size)
	{
		i = (i + 1) % N;
		j = (j + S[i]) % N;
		swap(&S[i], &S[j]);
		cyph = S[(S[i] + S[j]) % N];
		cypher[count] = cyph ^ plain[count];

		if (cypher[count] == '\r')
			flag = true;
		if (cypher[count] == '\n' && flag == true)
		{
			i = 0;
			j = 0;
			flag = false;
		}
		count++;

	}
	cypher[count] = '\0';
}

void	rc4(char *key, char *plain, unsigned char *cypher)
{
	int				size;
	unsigned char	S[N];

	permutation(key, S);
	size = ft_strlen(plain);
	generate(S, plain, size, cypher);
}
