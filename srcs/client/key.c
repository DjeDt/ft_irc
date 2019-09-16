/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:01:51 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/12 15:43:04 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	do_key_left(t_interface *inter, char *input)
{
	if  (inter->off > 0)
	{
		inter->off--;
		inter->cursor--;
		refresh_bot_interface(inter, input);
		return (true);
	}
	return (false);
}

bool	do_key_right(t_interface *inter, char *input)
{
	if (inter->off < inter->curmax && inter->off < inter->curmax)
	{
		inter->off++;
		inter->cursor++;
		refresh_bot_interface(inter, input);
		return (true);
	}
	return (false);
}

bool	do_key_up(t_interface *inter, char *input)
{
	(void)inter;
	(void)input;
	return (false);
}

bool	do_key_down(t_interface *inter, char *input)
{
	(void)inter;
	(void)input;
	return (false);
}

bool	insert_char(t_interface *inter, char *input, int c)
{
	if (inter->off < MAX_INPUT_LEN)
	{
		if (inter->off < inter->curmax)
			ft_memmove(input + (inter->off + 1), input + inter->off, ft_strlen(input + inter->off));
		input[inter->off] = c;
		inter->off++;
		inter->curmax++;
		inter->cursor++;
		inter->len++;
		refresh_bot_interface(inter, input);
		return (true);
	}
	else
	{
		refresh_bot_interface(inter, "max input lenght reached.");
		return (false);
	}
}

bool	delete_char(t_interface *inter, char *input)
{
	if (inter->off > 0)
	{
		inter->off--;
		inter->curmax--;
		inter->cursor--;
		inter->len--;
		ft_memmove(input + inter->off, input + inter->off + 1, inter->curmax - inter->off);
		input[inter->curmax] = '\0';
		refresh_bot_interface(inter, input);
		return (true);
	}
	return (false);
}
