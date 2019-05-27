/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:44:52 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/26 09:52:59 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

void		recurse_rb_insert(t_rbtree *root, t_rbtree *node)
{
	// do a function
	if (root != NULL && node->data.socket < root->data.socket)
	{
		if (root->left != NULL)
		{
			recurse_rb_insert(root->left, node);
			return ;
		}
		else
			root->left = node;
	}
	else if (root != NULL)
	{
		if (root->right != NULL)
		{
			recurse_rb_insert(root->right, node);
			return ;
		}
		else
			root->right = node;
	}
	node->parent = root;
	node->left = NULL;
	node->right = NULL;
	node->color = RB_RED;
}

void	rb_equalize(t_rbtree *node)
{
	if (parent(node) != NULL)
		case_one(node);
	else if (parent(node)->color == RB_BLACK)
		case_two(node);
	else if (uncle(node)->color == RB_RED)
		case_three(node);
	else
		case_four(node);
}

t_rbtree	*rb_create(t_user data)
{
	t_rbtree *new;

	if (!(new = malloc(sizeof(t_rbtree))))
		return (NULL);
	new->data = _memcpy(data);
	new->color = RB_BLACK;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	return (new);
}

void		rb_insert(t_rbtree **rt, t_user data, t_rbfunc *func)
{
	t_rbtree *root;
	t_rbtree *node;

	if (*rt == NULL)
	{
		*rt = rb_create(data);
		return (*root);
	}
	else
	{
		root = *rt;
		node = rb_create(data);
		recurse_rb_insert(root, node);
		rb_equalize(node);
		/* root = node; */
		/* while (parent(root) != NULL) */
		/* 	root = parent(root); */
		return (node);
	}
}
