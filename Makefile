#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:46:54 by pguillie          #+#    #+#              #
#    Updated: 2019/10/04 20:18:06 by ddinaut          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER	= server
CLIENT	= client

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I$(incdir)
EFLAGS	= -g3 -fsanitize=address

incdir	= ./incs/
srcdir	= ./srcs/
objdir	= .obj

# subdir
libdir		= lib/
clientdir	= client/
serverdir	= server/
cmddir		= command/
repliesdir	= replies/

server_src =							\
	$(serverdir)/server.c				\
	$(serverdir)/init_kill.c			\
	$(serverdir)/initialize.c			\
	$(serverdir)/runnin.c				\
	$(serverdir)/users.c				\
	$(serverdir)/users_search.c			\
	$(serverdir)/channel.c				\
	$(serverdir)/channel_users.c		\
	$(serverdir)/channel_users_remove.c	\
	$(serverdir)/interpreter.c			\
	$(serverdir)/circular.c				\
\
	$(serverdir)/$(cmddir)/help.c		\
	$(serverdir)/$(cmddir)/list.c		\
	$(serverdir)/$(cmddir)/join.c		\
	$(serverdir)/$(cmddir)/leave.c		\
	$(serverdir)/$(cmddir)/nick.c		\
	$(serverdir)/$(cmddir)/who.c		\
	$(serverdir)/$(cmddir)/message.c	\
	$(serverdir)/$(cmddir)/quit.c		\
	$(serverdir)/$(cmddir)/topic.c		\
	$(serverdir)/$(cmddir)/quit.c		\
	$(serverdir)/$(cmddir)/kill.c		\
\
	$(serverdir)/$(repliesdir)/unknow_command.c		\
	$(serverdir)/$(repliesdir)/notonchannel.c		\
	$(serverdir)/$(repliesdir)/nosuchchannel.c		\
	$(serverdir)/$(repliesdir)/toomanychannels.c	\
	$(serverdir)/$(repliesdir)/needmoreparams.c		\
	$(serverdir)/$(repliesdir)/nicknameinuse.c		\
	$(serverdir)/$(repliesdir)/erroneusnickname.c	\
	$(serverdir)/$(repliesdir)/erroneuschanname.c	\
	$(serverdir)/$(repliesdir)/erroneuschar.c		\
	$(serverdir)/$(repliesdir)/toomanyarguments.c	\
	$(serverdir)/$(repliesdir)/nosuchnick.c			\
	$(serverdir)/$(repliesdir)/topictoolong.c		\
	$(serverdir)/$(repliesdir)/rpl_topic.c			\
	$(serverdir)/$(repliesdir)/rpl_notopic.c		\
	$(serverdir)/$(repliesdir)/rpl_whoreply.c		\
	$(serverdir)/$(repliesdir)/rpl_endofwho.c		\
	$(serverdir)/$(repliesdir)/rpl_namreply.c		\
	$(serverdir)/$(repliesdir)/rpl_endofnames.c		\
	$(serverdir)/$(repliesdir)/rpl_liststart.c		\
	$(serverdir)/$(repliesdir)/rpl_list.c			\
	$(serverdir)/$(repliesdir)/rpl_endoflist.c		\
	$(serverdir)/$(repliesdir)/rpl_welcome.c		\
\
	$(libdir)/ft_isspace.c				\
	$(libdir)/ft_strlen.c				\
	$(libdir)/ft_arrlen.c				\
	$(libdir)/ft_memset.c				\
	$(libdir)/ft_memcpy.c				\
	$(libdir)/ft_memcmp.c				\
	$(libdir)/ft_memmove.c				\
	$(libdir)/ft_strchr.c				\
	$(libdir)/ft_itoa.c					\
	$(libdir)/ft_strndup.c				\
	$(libdir)/ft_strncmp.c				\
	$(libdir)/ft_strncat.c				\
	$(libdir)/ft_atoi.c					\
	$(libdir)/rc4_permutation.c			\
	$(libdir)/rc4.c						\
	$(libdir)/ft_swap.c					\
	$(libdir)/command_func.c

client_src = 							\
	$(clientdir)/client.c				\
	$(clientdir)/connect.c				\
	$(clientdir)/interface.c			\
	$(clientdir)/running.c				\
	$(clientdir)/interpreter.c			\
	$(clientdir)/circular.c				\
	$(clientdir)/key.c					\
\
	$(libdir)/ft_isspace.c				\
	$(libdir)/ft_strlen.c				\
	$(libdir)/ft_arrlen.c				\
	$(libdir)/ft_memset.c				\
	$(libdir)/ft_memcpy.c				\
	$(libdir)/ft_memcmp.c				\
	$(libdir)/ft_memmove.c				\
	$(libdir)/ft_strchr.c				\
	$(libdir)/ft_itoa.c					\
	$(libdir)/ft_strndup.c				\
	$(libdir)/ft_strncmp.c				\
	$(libdir)/ft_strncat.c				\
	$(libdir)/ft_atoi.c					\
	$(libdir)/ft_swap.c					\
	$(libdir)/rc4_permutation.c			\
	$(libdir)/rc4.c						\
	$(libdir)/command_func.c

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
