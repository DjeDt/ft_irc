/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:44:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/24 16:44:35 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

void	rotate_left(t_rbtree *node)
{
	t_rbtree *tmp;

	tmp = node->right;
	node->right = tmp->left;
	if (tmp->left != NULL)
		tmp->left->parent = node;

	tmp->parent = node->parent;
	if (node->parent == NULL)
		node = tmp;
	else if (node == node->parent->left)
		node->parent->left = tmp;
	else
		node->parent->right = tmp;

	tmp->left = node;
	node->parent = tmp;
}

void	rotate_right(t_rbtree *node)
{
	t_rbtree *tmp;

	tmp = node->left;
	node->left = tmp->right;
	if (tmp->right != NULL)
		tmp->right->parent = node;

	tmp->parent = node->parent;
	if (node->parent == NULL)
		node = tmp;
	else if (node == node->parent->right)
		node->parent->right = tmp;
	else
		node->parent->left = tmp;

	tmp->right = node;
	node->parent = tmp;
}
