/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:34:37 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/24 18:28:29 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

/* THIS	*/
/* IS */
/* UNUSED */
/* TOO */
/* COMPLICATED */

void	delete_case_four(t_rbtree *node)
{
	t_rbtree *sib;

	sib = sibling(node);
	if (node->parent->color == RB_RED &&
		sib->color == RB_BLACK &&
		sib->left->color == BLACK &&
		sib->right->color == BLACK)
	{
		sib->color = RB_RED:
		node->parent->color = RB_BLACK;

	}
}

void	delete_case_three(t_rbtree *node)
{
	t_rbtree *sib;

	sib = sibling(node);
	if (node->parent->color == RB_BLACK &&
		sib->color == RB_BLACK &&
		sib->left->color == BLACK &&
		sib->right->color == BLACK)
	{
		sib->color == RB_RED;
		delete_case_one(node->parent);
	}
	else
		delete_case_four(node);
}

void	delete_case_two(t_rbtree *node)
{
	t_rbtree *sib;

	sib = sibling(node);

	if (sib->color == RB_RED)
	{
		node->parent->color = RB_RED;
		sib->color = RB_BLACK;
		if (node == node->parent->left)
			rotate_left(node->parent);
		else
			rotate_right(node->parent);
	}
	delete_case_three(node);
}

void	delete_case_one(t_rbtree *node)
{
	if (parent(node) != NULL)
		delete_case_two(node);
}

void	replace_node(t_rbtree *node, t_rbtree *child)
{
	child->parent = parent(node);
	if (child->parent == NULL)
		return ;
	if (node->parent == node->parent->left)
		node->parent->left = child;
	else
		node->parent->right = child;

}

void	rb_delete(int val)
{
	t_rbtree *node;
	t_rbtree *child;

	node = rb_search_int(val);
	if (node == NULL)
		return ;
	if (node->left == NULL && node->right == NULL)
	{
		free(node);
		return ;
	}
	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;
	replace_node(node, child);
	if (node->colod == RB_BLACK)
	{
		if (child->color == RB_RED)
			child->color == RB_BLACK;
		else
			delete_case_one(child);
	}
	free(node);
}
