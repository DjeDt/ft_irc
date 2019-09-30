/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:06:15 by Dje               #+#    #+#             */
/*   Updated: 2019/09/30 15:14:48 by Dje              ###   ########.fr       */
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

static void	permutation(char *key, unsigned char *cypher)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < N)
	{
		cypher[i] = i;
		i++;
	}
	i = 0;
	while (i < N)
	{
		j = (j + cypher[i] + key[i % KEY_LEN]) % N;
		swap(&cypher[i], &cypher[j]);
		i++;
	}
}

static void	reset(t_r4 *r4, int *i, int *j)
{
	*i = 0;
	*j = 0;
	r4->flag = false;
	permutation(r4->key, r4->cypher);
}

static void	generate(t_r4 r4, unsigned char *plain, unsigned char *encrypted)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	r4.flag = false;
	while (count < r4.size)
	{
		i = (i + 1) % N;
		j = (j + r4.cypher[i]) % N;
		swap(&r4.cypher[i], &r4.cypher[j]);
		r4.cyph = r4.cypher[(r4.cypher[i] + r4.cypher[j]) % N];
		encrypted[count] = r4.cyph ^ plain[count];
		if (encrypted[count] == '\r')
			r4.flag = true;
		if (encrypted[count] == '\n' && r4.flag == true)
			reset(&r4, &i, &j);
		count++;
	}
	encrypted[count] = '\0';
}

void		rc4(char *key, unsigned char *plain, \
					unsigned char *encrypted, int size)
{
	t_r4 r4;

	r4.size = size;
	r4.key = key;
	permutation(r4.key, r4.cypher);
	generate(r4, plain, encrypted);
}
