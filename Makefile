# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 15:24:31 by grmullin          #+#    #+#              #
#    Updated: 2025/01/23 17:22:46 by lhagemos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
FILES := main.c \
signal.c \
delete_later.c \
Init/init.c \
Init/free.c \
Execution/ft_command.c \
Execution/exec.c \
Execution/exec_utils.c \
Execution/Heredoc/heredoc.c \
Execution/Heredoc/heredoc_expand.c \
Execution/Heredoc/heredoc_utils.c \
Execution/redir_in.c \
Execution/redir_out.c \
Parsing/two_tokens.c \
Execution/Builtins/builtins.c \
Execution/Builtins/what.c \
Execution/Builtins/exit.c \
Execution/Builtins/ft_builtins.c \
Execution/Builtins/unset.c \
Execution/Builtins/Export/export.c \
Execution/Builtins/Export/elist.c \
Execution/Builtins/Export/exp_utils1.c \
Execution/Builtins/Export/exp_utils2.c \
Lexing/lexing.c \
Lexing/lexing_utils.c \
Lexing/utils.c \
Lexing/token.c \
Lexing/syntax.c \
Parsing/build_tree.c \
Parsing/get_root.c \
Parsing/parsing_utils.c \
Init/error.c \
Preparsing/preparsing.c \
Preparsing/env.c \
Preparsing/prep_utils.c \
Preparsing/env_utils.c \
Preparsing/env_utils2.c \
Preparsing/cmd_utils.c \
Preparsing/path.c \
Preparsing/whitespace.c \

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
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re