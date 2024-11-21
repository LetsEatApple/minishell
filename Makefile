# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 15:24:31 by grmullin          #+#    #+#              #
#    Updated: 2024/11/21 15:41:55 by lhagemos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
FILES := main.c \
utils.c
OBJS := $(FILES:.c=.o)
MINISHELL_H := minishell.h
CC := cc
CFLAGS := -Wall -Werror -Wextra -g -fPIE 
LDFLAGS := -pie -lreadline
RM := rm -f
RMDIR := -rmdir

all: $(MINISHELL_H) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(LDFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS) *.gch

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re