/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:01:51 by ddinaut           #+#    #+#             */
/*   Updated: 2019/10/01 10:57:36 by Dje              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	do_key_left(t_interface *inter, char *input)
{
	if (inter->off > 0)
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

bool	insert_char(t_interface *inter, char *input, int c)
{
	int len;

	if (inter->off < MAX_INPUT_LEN && inter->len < MAX_INPUT_LEN)
	{
		len = ft_strlen(input + inter->off);
		if (inter->off < inter->curmax)
			ft_memmove(input + (inter->off + 1), input + inter->off, len);
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
	if (inter->off > 0 && inter->len > 0)
	{
		inter->off--;
		inter->curmax--;
		inter->cursor--;
		inter->len--;
		ft_memmove(input + inter->off, input + inter->off + 1, \
			inter->curmax - inter->off);
		input[inter->off] = '\0';
		refresh_bot_interface(inter, input);
		return (true);
	}
	return (false);
}
