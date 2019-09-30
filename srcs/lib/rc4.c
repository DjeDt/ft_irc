/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:06:15 by Dje               #+#    #+#             */
/*   Updated: 2019/09/30 16:36:49 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	reset(t_r4 *r4, int *i, int *j)
{
	*i = 0;
	*j = 0;
	r4->flag = false;
	rc4_permutation(r4->key, r4->cypher);
}

static void	generate_encrypt(t_r4 *r4, unsigned char *plain, \
							unsigned char *encrypted)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (count < r4->size)
	{
		i = (i + 1) % N;
		j = (j + r4->cypher[i]) % N;
		ft_swap(&r4->cypher[i], &r4->cypher[j]);
		r4->cyph = r4->cypher[(r4->cypher[i] + r4->cypher[j]) % N];
		encrypted[count] = r4->cyph ^ plain[count];
		if (plain[count] == '\r')
			r4->flag = true;
		if (plain[count] == '\n' && r4->flag == true)
			reset(r4, &i, &j);
		count++;
	}
	encrypted[count] = '\0';
}

static void	generate_decrypt(t_r4 *r4, unsigned char *plain, \
							unsigned char *decrypted)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (count < r4->size)
	{
		i = (i + 1) % N;
		j = (j + r4->cypher[i]) % N;
		ft_swap(&r4->cypher[i], &r4->cypher[j]);
		r4->cyph = r4->cypher[(r4->cypher[i] + r4->cypher[j]) % N];
		decrypted[count] = r4->cyph ^ plain[count];
		if (decrypted[count] == '\r')
			r4->flag = true;
		if (decrypted[count] == '\n' && r4->flag == true)
			reset(r4, &i, &j);
		count++;
	}
	decrypted[count] = '\0';
}

void		rc4_decrypt(char *key, unsigned char *encrypted, \
					unsigned char *decrypted, int size)
{
	t_r4 r4;

	r4.key = key;
	r4.size = size;
	r4.flag = false;
	rc4_permutation(r4.key, r4.cypher);
	generate_decrypt(&r4, encrypted, decrypted);
}

void		rc4_encrypt(char *key, unsigned char *plain, \
					unsigned char *encrypted, int size)
{
	t_r4 r4;

	r4.key = key;
	r4.size = size;
	r4.flag = false;
	rc4_permutation(r4.key, r4.cypher);
	generate_encrypt(&r4, plain, encrypted);
}
