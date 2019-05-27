/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:45:52 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/24 16:46:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

void	case_one(t_rbtree *node)
{
	if (parent(node) == NULL)
		node->color = RB_BLACK;
}

void	case_two(t_rbtree *node)
{
	(void)node;
	return ;
}

void	case_three(t_rbtree *node)
{
	t_rbtree *tmp;

	parent(node)->color = RB_BLACK;
	uncle(node)->color = RB_BLACK;
	tmp = grandparent(node);
	tmp->color = RB_RED;
	rb_equalize(tmp);
}

void	case_four(t_rbtree *node)
{
	t_rbtree *p;
	t_rbtree *gp;

	p = parent(node);
	gp = grandparent(node);

	if (node == gp->left->right)
	{
		rotate_left(p);
		node = node->left;
	}
	else if (node == gp->right->left)
	{
		rotate_left(p);
		node = node->right;
	}
	case_four_extra(node);
}

void	case_four_extra(t_rbtree *node)
{
	t_rbtree *p;
	t_rbtree *gp;

	p = parent(node);
	gp = grandparent(node);
	if (node == p->left)
		rotate_right(gp);
	else
		rotate_left(gp);
	p->color = RB_BLACK;
	gp->color = RB_RED;
}
