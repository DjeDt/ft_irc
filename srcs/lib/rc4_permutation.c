/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4_permutation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 16:34:19 by Dje               #+#    #+#             */
/*   Updated: 2019/09/30 16:35:13 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	rc4_permutation(char *key, unsigned char *cypher)
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
		ft_swap(&cypher[i], &cypher[j]);
		i++;
	}
}
