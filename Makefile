#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:46:54 by pguillie          #+#    #+#              #
#    Updated: 2019/04/22 20:53:51 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER	= server
CLIENT	= client

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I$(incdir)

incdir	= ./incs/
srcdir	= ./srcs/
objdir	= .obj

server_src =			\
	server.c			\
	initialize.c		\
	runnin.c			\
	add_users.c			\
	receive.c			\
	send.c				\
	error.c				\
	error_functions.c	\
	logger.c			\
	lib.c

client_src = \
	client.c

server_obj = $(addprefix $(srcdir), $(server_src:%.c=%.o))
client_obj = $(addprefix $(srcdir), $(client_src:%.c=%.o))

.PHONY: all clean fclean re

all: $(SERVER) $(CLIENT)

$(SERVER): $(server_obj)
	$(CC) -o $@ $^
$(CLIENT): $(client_obj)
	$(CC) -o $@ $^

$(server_obj) $(client_obj): $(include) Makefile

clean:
	$(RM) $(server_obj) $(client_obj)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all
