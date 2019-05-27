/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:43:52 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/24 16:44:07 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

t_rbtree	*parent(t_rbtree *node)
{
	return (node->parent);
}

t_rbtree	*grandparent(t_rbtree *node)
{
	t_rbtree *tmp;

	tmp = parent(node);
	if (tmp != NULL)
		return (parent(tmp));
	return (NULL);
}

t_rbtree	*sibling(t_rbtree *node)
{
	t_rbtree *tmp;

	tmp = parent(node);
	if (tmp != NULL)
	{
		if (node == tmp->left)
			return (tmp->right);
		else
			return (tmp->left);
	}
	return (NULL);
}

t_rbtree	*uncle(t_rbtree *node)
{
	t_rbtree *tmp;

	if (grandparent(node) != NULL)
	{
		tmp = parent(node);
		return (sibling(tmp));
	}
	return (NULL);
}
