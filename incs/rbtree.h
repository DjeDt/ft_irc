/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:41:25 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/24 21:41:57 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_H
# define RBTREE_H

# include <stdlib.h>
# include <stdio.h>

enum rb_color
{
    RB_BLACK,
    RB_RED
};

typedef void (t_rbfunc) (void *, void *);

// same struct in 'server.h'
typedef struct			s_user
{
	int					socket;
	int					statut;
	char				nick[MAX_NICK_LEN];
	struct sockaddr_in	addr;
}						t_user;

typedef struct			s_rbtree
{
	t_user				data;
    enum rb_color		color;
    struct s_rbtree		*left;
    struct s_rbtree		*right;
    struct s_rbtree		*parent;
}						t_rbtree;

/* family */
t_rbtree				*parent(t_rbtree *node);
t_rbtree				*grandparent(t_rbtree *node);
t_rbtree				*sibling(t_rbtree *node);
t_rbtree				*uncle(t_rbtree *node);

/* rotate */
void					rotate_left(t_rbtree *node);
void					rotate_right(t_rbtree *node);

/* manage */
t_rbtree				*rb_create(t_user data);
void					rb_insert(t_rbtree **rt, t_user data, t_rbfunc *func);
void					recurse_rb_insert(t_rbtree *root, t_rbtree *node);

/* manage misc */
void					rb_iterate(t_rbtree *node);

/* case */
void					rb_equalize(t_rbtree *node);
void					case_one(t_rbtree *node);
void					case_two(t_rbtree *node);
void					case_three(t_rbtree *node);
void					case_four(t_rbtree *node);
void					Case_four_extra(t_rbtree *node);

#endif
