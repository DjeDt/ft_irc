#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:46:54 by pguillie          #+#    #+#              #
#    Updated: 2019/08/04 19:32:58 by ddinaut          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER	= server
CLIENT	= client

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I$(incdir)
EFLAGS	= #-g3 -fsanitize=address

incdir	= ./incs/
srcdir	= ./srcs/
objdir	= .obj

# subdir
libdir		= lib/
clientdir	= client/
serverdir	= server/
cmddir		= command/

server_src =							\
	$(serverdir)/server.c				\
	$(serverdir)/initialize.c			\
	$(serverdir)/runnin.c				\
	$(serverdir)/users.c				\
	$(serverdir)/channel.c				\
	$(serverdir)/channel_users.c		\
	$(serverdir)/receive.c				\
	$(serverdir)/interpreter.c			\
	$(serverdir)/send.c					\
	$(serverdir)/error.c				\
	$(serverdir)/error_functions.c		\
\
	$(serverdir)/$(cmddir)/help.c		\
	$(serverdir)/$(cmddir)/list.c		\
	$(serverdir)/$(cmddir)/join.c		\
	$(serverdir)/$(cmddir)/leave.c		\
	$(serverdir)/$(cmddir)/nick.c		\
	$(serverdir)/$(cmddir)/who.c		\
	$(serverdir)/$(cmddir)/msg.c		\
	$(serverdir)/$(cmddir)/quit.c		\
	$(serverdir)/$(cmddir)/connect.c	\
	$(serverdir)/$(cmddir)/quit.c		\
	$(serverdir)/$(cmddir)/shutdw.c		\
	\
	$(libdir)/logger.c					\
	$(libdir)/lib.c						\
	$(libdir)/strtok.c


client_src = 							\
	$(clientdir)/client.c				\
	$(clientdir)/interface.c			\
	$(clientdir)/running.c				\
	$(clientdir)/interpreter.c			\
	$(clientdir)/key.c					\
	$(clientdir)/send.c					\
	$(clientdir)/receive.c				\
\
	$(clientdir)/$(cmddir)/connect.c	\
	$(clientdir)/$(cmddir)/msg.c		\
	$(clientdir)/$(cmddir)/who.c		\
	$(clientdir)/$(cmddir)/list.c		\
	$(clientdir)/$(cmddir)/nick.c		\
	$(clientdir)/$(cmddir)/help.c		\
	$(clientdir)/$(cmddir)/quit.c		\
	$(clientdir)/$(cmddir)/join.c		\
	$(clientdir)/$(cmddir)/leave.c		\
\
	$(libdir)/logger.c					\
	$(libdir)/lib.c						\
	$(libdir)/strtok.c


server_obj = $(addprefix $(srcdir), $(server_src:%.c=%.o))
client_obj = $(addprefix $(srcdir), $(client_src:%.c=%.o))

.PHONY: all clean fclean re

all: $(SERVER) $(CLIENT)

$(SERVER): $(server_obj)
	$(CC) $(EFLAGS) -o $@ $^

$(CLIENT): $(client_obj)
	$(CC) $(EFLAGS) -lncurses -o $@ $^

$(server_obj) $(client_obj): $(include) Makefile

clean:
	$(RM) $(server_obj) $(client_obj)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all
