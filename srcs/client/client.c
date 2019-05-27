/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:31:12 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/28 01:57:49 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

typedef struct	s_interface
{
	WINDOW		*top;
	WINDOW		*bot;
	int			line;
	int			cursor;
	int			curmax;
}				t_interface;

void	refresh_top_interface(t_interface *inter, char *input)
{
	box(inter->top, ACS_VLINE, ACS_HLINE);
	mvwprintw(inter->top, inter->line, 1, "%s", input);
	wrefresh(inter->top);
}

void	refresh_bot_interface(t_interface *inter, char *input)
{
	box(inter->bot, ACS_VLINE, ACS_HLINE);
	mvwprintw(inter->bot, 1, 1, "> %s", input);
	wmove(inter->bot, 1, inter->cursor);
	wrefresh(inter->bot);
}

bool	init_interface(t_interface *inter)
{
	inter->line = 1;
	inter->cursor = 3;
	inter->curmax = 0;

    initscr();
	noecho();
	cbreak();

	inter->top = subwin(stdscr, LINES - BOX_INPUT_LEN, COLS, 0, 0);
	inter->bot = subwin(stdscr, BOX_INPUT_LEN, COLS, LINES - BOX_INPUT_LEN, 0);

	if (!inter->top || !inter->bot)
		return (false);

	keypad(inter->bot, TRUE);

	refresh_top_interface(inter, "");
	refresh_bot_interface(inter, "");

	return (true);
}

void	flush_and_reset(t_interface *inter, char *input)
{
	inter->line++;
	inter->curmax = 0;
	inter->cursor = 3;
	wclear(inter->bot);
	refresh_top_interface(inter, input);
	memset(input, 0x0, 510);
}

void	get_input(t_interface *inter)
{
	int		c;
	int		off;
	char	input[510] = {0};

	off = 0;
	while (true)
	{
		c = wgetch(inter->bot);
		if (c == KEY_LEFT)
		{
			if  (off > 0)
			{
				inter->cursor--;
				off--;
			}
		}
		else if (c == KEY_RIGHT)
		{
			if (off < inter->curmax)
			{
				inter->cursor++;
				off++;
			}
		}
		else if (c == KEY_UP || c == KEY_DOWN)
			;
		else if (c == 'q')
			return ;
		else if (c == KEY_ENTER || c == '\n')
		{
			off = 0;
			flush_and_reset(inter, input);
		}
		else if (c < 510)
		{
			inter->curmax++;
			inter->cursor++;
			input[off++] = c;
		}
		refresh_bot_interface(inter, input);
	}
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_interface inter;

	if (init_interface(&inter) != true)
		return (-1);
	get_input(&inter);
	endwin();
	return (0);
}
