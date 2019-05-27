/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbmisc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:48:45 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/24 16:56:37 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

void	rb_iterate(t_rbtree *node)
{
	if (node != NULL)
	{
		if (node->left != NULL)
			rb_iterate(node->left);
		if (node->right != NULL)
			rb_iterate(node->right);
		printf("data = %p\n", node->data);
	}
}
