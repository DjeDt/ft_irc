/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dje <ddinaut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 16:27:50 by Dje               #+#    #+#             */
/*   Updated: 2019/09/30 16:29:10 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_swap(unsigned char *x, unsigned char *y)
{
	int tmp;

	tmp = (*x);
	(*x) = (*y);
	(*y) = tmp;
}
