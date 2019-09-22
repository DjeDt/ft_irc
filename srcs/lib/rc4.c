/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:06:15 by Dje               #+#    #+#             */
/*   Updated: 2019/09/22 16:46:58 by Dje              ###   ########.fr       */
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

#define I		0
#define J		1
#define COUNT	2
#define CYPH	3

static void	reset(int *tab, unsigned char *S, char *key, bool flag)
{
	tab[I] = 0;
	tab[J] = 0;
	flag = false;
	permutation(key, S);
}

static void	generate(unsigned char *S, char *key, unsigned char *plain, int size, unsigned char *cypher)
{
	bool flag;
	int	tab[4];

	tab[I] = 0;
	tab[J] = 0;
	tab[COUNT] = 0;
	tab[CYPH] = 0;
	flag = false;
	while (tab[COUNT] <= size)
	{
		tab[I] = (tab[I] + 1) % N;
		tab[J] = (tab[J] + S[tab[I]]) % N;
		swap(&S[tab[I]], &S[tab[J]]);
		tab[CYPH] = S[(S[tab[I]] + S[tab[J]]) % N];
		cypher[tab[COUNT]] = tab[CYPH] ^ plain[tab[COUNT]];
		if (cypher[tab[COUNT]] == '\r')
			flag = true;
		if (cypher[tab[COUNT]] == '\n' && flag == true)
			reset(tab, S, key, flag);
		tab[COUNT]++;
	}
	cypher[tab[COUNT]] = '\0';
}

void	rc4(char *key, unsigned char *plain, unsigned char *cypher, int size)
{
	unsigned char	S[N];

	permutation(key, S);
	generate(S, key, plain, size, cypher);
}
