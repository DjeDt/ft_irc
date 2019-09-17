/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:04:28 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/13 17:40:58 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	zeroed(t_interface *inter)
{
	inter->off = 0;
	inter->line = LINE_START;
	inter->cursor = CURSOR_START;
	inter->curmax = 0;
	inter->len = 0;
}

bool		init_interface(t_interface *inter)
{
	zeroed(inter);
	initscr();
	inter->top = subwin(stdscr, LINES - BOX_INPUT_LEN, COLS, 0, 0);
	inter->bot = subwin(stdscr, BOX_INPUT_LEN, COLS, LINES - BOX_INPUT_LEN, 0);
	if (!inter->top || !inter->bot)
		return (false);
	noecho();
	cbreak();
	scrollok(inter->top, TRUE);
	keypad(inter->bot, TRUE);
	box(inter->top, ACS_VLINE, ACS_HLINE);
	box(inter->bot, ACS_VLINE, ACS_HLINE);
	wprintw(inter->top, "\n");
	mvwprintw(inter->bot, 1, 1, "> ");
	wnoutrefresh(inter->top);
	wnoutrefresh(inter->bot);
	doupdate();
	inter->status = true;
	return (true);
}

void		stop_interface(t_interface *inter)
{
	delwin(inter->top);
	delwin(inter->bot);
	endwin();
}

void		refresh_top_interface(t_interface *inter, char *input, ...)
{
	va_list	arglist;
	char	data[MAX_INPUT_LEN + 3];

	ft_memset(data, 0x0, MAX_INPUT_LEN + 3);
	va_start(arglist, input);
	vsnprintf(data, MAX_INPUT_LEN + 3, input, arglist);
	va_end(arglist);
	if (inter->status == false)
	{
		printf(" %s\n", data);
		return ;
	}
	wprintw(inter->top, " %s\n", data);
	box(inter->top, ACS_VLINE, ACS_HLINE);
	wmove(inter->bot, 1, inter->cursor);
	wnoutrefresh(inter->top);
	wnoutrefresh(inter->bot);
	doupdate();
}

void		refresh_bot_interface(t_interface *inter, char *input)
{
	if (inter->status == false)
	{
		printf("\r> %s", input);
		return ;
	}
	wclear(inter->bot);
	box(inter->bot, ACS_VLINE, ACS_HLINE);
	mvwprintw(inter->bot, 1, 1, "> %s", input);
	wmove(inter->bot, 1, inter->cursor);
	wnoutrefresh(inter->bot);
	doupdate();
}
