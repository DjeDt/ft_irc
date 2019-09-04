/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:04:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 23:53:28 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	init_interface(t_interface *inter)
{
	inter->off = 0;
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

	scrollok(inter->top, TRUE);
	keypad(inter->bot, TRUE);

	// draw interface
	box(inter->top, ACS_VLINE, ACS_HLINE);
	box(inter->bot, ACS_VLINE, ACS_HLINE);

	// move the cursor to the input box
	wprintw(inter->top, "\n");
	mvwprintw(inter->bot, 1, 1, "> ");

	// refresh term
	wnoutrefresh(inter->top);
	wnoutrefresh(inter->bot);

	doupdate();

	return (true);
}

void	refresh_top_interface(t_interface *inter, char *input, ...)
{
	va_list	arglist;
	char	data[MAX_INPUT_LEN + 1] = {0};

	va_start(arglist, input);
	vsnprintf(data, MAX_INPUT_LEN, input, arglist);
	va_end(arglist);

	wprintw(inter->top, " %s", data);
	box(inter->top, ACS_VLINE, ACS_HLINE);
	wnoutrefresh(inter->top);
	doupdate();
}

void	refresh_bot_interface(t_interface *inter, char *input)
{
	wclear(inter->bot);
	box(inter->bot, ACS_VLINE, ACS_HLINE);
	mvwprintw(inter->bot, 1, 1, "> %s", input);
	wmove(inter->bot, 1, inter->cursor);
	wnoutrefresh(inter->bot);
	doupdate();
}
