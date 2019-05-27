/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:14:26 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/26 22:36:28 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		btree_find_min(t_btree *node)
{
	if (node == NULL)
		return (-1);
	if (node->right != NULL)
		btree_find_min(node->right);
	return (node->data.socket);
}

void	btree_delete_node_int(t_btree **root, int key)
{
	t_btree *rt;
	t_btree *tmp;

   	if (*root == NULL)
		return ;
	rt = (*root);
	if (key < rt->data.socket)
		btree_delete_node_int(&rt->left, key);
	else if (key > rt->data.socket)
		btree_delete_node_int(&rt->right, key);
	else
	{
		tmp = rt;
		if (rt->left == NULL && rt->right == NULL)
		{
			free(rt);
			(*root) = NULL;
			puts("delete 1");
		}
		else if (rt->left == NULL)
		{
			free(&rt->right);
			rt = tmp->right;
			puts("delete 2");
		}
		else if (rt->right == NULL)
		{
			free(&rt->left);
			rt = tmp->left;
			puts("delete3");
		}
		else
		{
			puts("delete recurse");
			btree_delete_node_int(&rt->right, btree_find_min(rt->right));
			rt = rt->right;
		}
	}
}

t_btree		*btree_create_node(t_user data)
{
	t_btree *new;

	if (!(new = (t_btree*)malloc(sizeof(t_btree))))
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->root = NULL;
	_memcpy(&new->data, &data, sizeof(t_user));
	//new->item = _memcpy(item);
	return (new);
}

void		btree_insert_data_int(t_btree **root, t_user data, int (*func)(int, int))
{
	if ((*root) == NULL)
		(*root) = btree_create_node(data);
	else if ((*func)(data.socket, (*root)->data.socket) < 0)
	{
		btree_insert_data_int(&(*root)->left, data, func);
		(*root)->left->root = (*root);
	}
	else
	{
		btree_insert_data_int(&(*root)->right, data, func);
		(*root)->right->root = (*root);
	}
}

void		btree_insert_data_char(t_btree **root, t_user data, int (*func)(char*, char*))
{
	if ((*root) == NULL)
		(*root) = btree_create_node(data);
	else if ((*func)(data.nick, (*root)->data.nick) < 0)
	{
		btree_insert_data_char(&(*root)->left, data, func);
		(*root)->left->root = (*root);
	}
	else
	{
		btree_insert_data_char(&(*root)->right, data, func);
		(*root)->right->root = (*root);
	}
}

t_btree		*btree_search_data_int(t_btree *root, int ref, int (*func)(int, int))
{
	t_btree	*node;

	if (root && ref)
	{
		if ((node = btree_search_data_int(root->left, ref, func)))
			return (node);
		if (func(root->data.socket, ref) == 0)
			return (root);
		if ((node = btree_search_data_int(root->right, ref, func)))
			return (node);
	}
	return (NULL);
}

t_btree		*btree_search_data_char(t_btree *root, char *ref, int (*func)(char *, char *))
{
	t_btree *node;

	if (root && ref)
	{
		if ((node = btree_search_data_char(root->left, ref, func)))
			return (node);
		if (func(root->data.nick, ref) == 0)
			return (root);
		if ((node = btree_search_data_char(root->right, ref, func)))
			return (node);
	}
	return (NULL);
}
