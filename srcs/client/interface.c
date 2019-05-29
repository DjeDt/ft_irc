/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:04:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/05/28 17:30:29 by ddinaut          ###   ########.fr       */
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

	nodelay(stdscr, TRUE);
	keypad(inter->bot, TRUE);

	refresh_top_interface(inter, "");
	refresh_bot_interface(inter, "");
	return (true);
}

void	refresh_top_interface(t_interface *inter, char *input)
{
	box(inter->top, ACS_VLINE, ACS_HLINE);
	mvwprintw(inter->top, inter->line, 1, "%s", input);
	inter->line++;
	wrefresh(inter->top);
}

void	refresh_bot_interface(t_interface *inter, char *input)
{
	wclear(inter->bot);
	box(inter->bot, ACS_VLINE, ACS_HLINE);
	mvwprintw(inter->bot, 1, 1, "> %s", input);
	wmove(inter->bot, 1, inter->cursor);
	wrefresh(inter->bot);
}
