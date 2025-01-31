# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 15:24:31 by grmullin          #+#    #+#              #
#    Updated: 2025/01/31 21:04:49 by lhagemos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
FILES := src/main.c \
src/Signals/signal.c \
src/Signals/signal_hdoc.c \
src/debug.c \
src/Init/init.c \
src/Init/free.c \
src/Execution/ft_command.c \
src/Execution/exec.c \
src/Execution/exec_utils.c \
src/Execution/handle_pipe.c \
src/Preparsing/Heredoc/heredoc.c \
src/Preparsing/Heredoc/heredoc_expand.c \
src/Preparsing/Heredoc/heredoc_utils.c \
src/Execution/handle_redir_in.c \
src/Execution/handle_redir_out.c \
src/Parsing/two_tokens.c \
src/Execution/Builtins/builtins.c \
src/Execution/Builtins/what.c \
src/Execution/Builtins/exit.c \
src/Execution/Builtins/ft_builtins.c \
src/Execution/Builtins/unset.c \
src/Execution/Builtins/Export/export.c \
src/Execution/Builtins/Export/elist.c \
src/Execution/Builtins/Export/exp_utils1.c \
src/Execution/Builtins/Export/exp_utils2.c \
src/Lexing/lexing.c \
src/Lexing/lexing_utils.c \
src/Lexing/utils.c \
src/Lexing/token.c \
src/Lexing/syntax.c \
src/Parsing/build_tree.c \
src/Parsing/get_op.c \
src/Parsing/parsing_utils.c \
src/Init/error.c \
src/Preparsing/preparsing.c \
src/Preparsing/env.c \
src/Preparsing/prep_utils.c \
src/Preparsing/env_utils.c \
src/Preparsing/env_utils2.c \
src/Preparsing/cmd_utils.c \
src/Preparsing/path.c \
src/Preparsing/whitespace.c \

OBJS := $(FILES:.c=.o)
MINISHELL_H := ./include/minishell.h
CC := cc
CFLAGS := -Wall -Werror -Wextra -g -fPIE 
LDFLAGS := -pie -lreadline -lncurses
RM := rm -f
RMDIR := -rmdir

LIBFT_DIR := ./src/Libft
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