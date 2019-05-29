/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:01:51 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/28 15:02:45 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	do_key_left(t_interface *inter, char *input)
{
	if  (inter->off > 0 && inter->cursor > CURSOR_START)
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
	if (inter->off < inter->curmax && (inter->cursor - CURSOR_START) < inter->curmax)
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
	if (inter->off < MAX_INPUT_LEN && inter->curmax < MAX_INPUT_LEN)
	{
		inter->curmax++;
		inter->cursor++;
		input[inter->off] = c;
		inter->off++;
		refresh_bot_interface(inter, input);
		return (true);
	}
	else
	{
		refresh_bot_interface(inter, "max input lenght reached.");
		return (false);
	}
}
