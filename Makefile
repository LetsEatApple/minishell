# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 15:24:31 by grmullin          #+#    #+#              #
#    Updated: 2024/11/22 16:05:47 by grmullin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
FILES := main.c Init/init.c Init/free.c Environment/env_vars.c Execution/Builtins/builtins.c
OBJS := $(FILES:.c=.o)
MINISHELL_H := minishell.h
CC := cc
CFLAGS := -Wall -Werror -Wextra -g -fPIE 
LDFLAGS := -pie -lreadline -lncurses
RM := rm -f
RMDIR := -rmdir

LIBFT_DIR := ./Libft
LIBFT := $(LIBFT_DIR)/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): 
	make -C $(LIBFT_DIR) -s

$(NAME): $(LIBFT) $(MINISHELL_H) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re