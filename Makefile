# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 15:24:31 by grmullin          #+#    #+#              #
#    Updated: 2024/12/13 12:48:47 by grmullin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
FILES := main.c \
delete_later.c \
Init/init.c \
Init/free.c \
Environment/env_vars.c \
Execution/ft_command.c \
Execution/exec.c \
Execution/exec_utils.c \
Execution/Builtins/builtins.c \
Execution/Builtins/ft_echo.c \
Lexing/lexing.c \
Lexing/lexing_utils.c \
Lexing/utils.c \
Lexing/token.c \
Parsing/build_tree.c \
Parsing/get_root.c \
Parsing/parsing_utils.c \
error.c \
Preparsing/preparsing.c \
Preparsing/env.c \
Preparsing/prep_utils.c \
Preparsing/env_utils.c \
Preparsing/cmd_utils.c \
Preparsing/path.c \

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
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): 
	@make -C $(LIBFT_DIR) -s

$(NAME): $(LIBFT) $(MINISHELL_H) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re