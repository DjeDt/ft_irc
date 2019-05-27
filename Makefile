#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:46:54 by pguillie          #+#    #+#              #
#    Updated: 2019/05/26 22:07:31 by ddinaut          ###   ########.fr        #
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
rbtreedir	= rbtree/

server_src =						\
	$(serverdir)/server.c			\
	$(serverdir)/initialize.c		\
	$(serverdir)/runnin.c			\
	$(serverdir)/add_users.c		\
	$(serverdir)/receive.c			\
	$(serverdir)/interpreter.c		\
	$(serverdir)/send.c				\
	$(serverdir)/error.c			\
	$(serverdir)/error_functions.c	\
	\
	$(libdir)/logger.c				\
	$(libdir)/lib.c					\
	$(libdir)/strtok.c				\
	$(libdir)/tree.c				\

client_src = 					\
	$(clientdir)/client.c		\
	$(clientdir)/running.c		\
	$(clientdir)/interpreter.c	\
	$(clientdir)/receive.c		\
	$(clientdir)/connect.c		\
	$(clientdir)/error.c		\
	\
	$(libdir)/logger.c			\
	$(libdir)/lib.c				\
	$(libdir)/strtok.c

server_obj = $(addprefix $(srcdir), $(server_src:%.c=%.o))
client_obj = $(addprefix $(srcdir), $(client_src:%.c=%.o))

.PHONY: all clean fclean re

all: $(SERVER) $(CLIENT)

$(SERVER): $(server_obj)
	$(CC) $(EFLAGS) -o $@ $^
$(CLIENT): $(client_obj)
	$(CC) $(EFLAGS) -o $@ $^

$(server_obj) $(client_obj): $(include) Makefile

clean:
	$(RM) $(server_obj) $(client_obj)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all
