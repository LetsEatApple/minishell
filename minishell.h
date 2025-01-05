/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:21:45 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/05 22:22:10 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <linux/limits.h>
# include "structs.h"
# include "Libft/libft.h"

extern volatile __sig_atomic_t	g_signal;

void			init_msh(t_data *data);
void			free_data(t_data *data);
int				init_data(t_data *data, int ac, char **envp);
void			handle_sig(int sig);
int				is_whitespace(char c);
int				print_env(char **env);

/*              Builtins            */
int				is_built_in(char *cmd);
int				ft_built_ins(t_data *data, char **cmd);
int				ft_echo(char **cmd);
int				ft_arrlen(char **cmd);
int				ft_pwd(t_data *data, char **cmd);
char			*getpwd();
int				ft_exit(t_data *data, char **cmd);
int				ft_export(t_data *data, char **cmd);
void			clear_elist(t_env **head);
t_env			*arr2list(t_data *data);
int				lst_size(t_env *head, int i);
void			make_list(t_env **head, char *value, int exp);
int				is_smaller(char *next, char *min, int ind);
int				check_var(char *s, t_env *head);
void			replace_val(char *s, t_env **head);
void			reset_index(t_env **head);
char			**list2arr(t_data *data);
int				charnstr(char *s, char c);
int				split_point(char *s);
void			print_exp_var(t_env *evar);
int				ft_unset(t_data *data, char **cmd);
int				ft_cd(t_data *data, char **cmd);

/*             Execution           */
void			ft_command(t_data *data, char **cmd);
void			execute(t_data *data, t_node *node);
void			handle_pipe(t_data *data, t_node *node);
int				ft_wait(int pid1, t_node *node);
void			handle_redir_in(t_data *data, t_node *node);
void			handle_redir_out(t_data *data, t_node *node);
void			handle_redir_append(t_data *data, t_node *node);
char			*ft_get_first_word(char *s);
void			ft_exec(t_data *data, char **cmd);
void			handle_two_tokens(t_data *data);
void			ft_printf_fd(char *print);

/*              Env.vars            */
int				get_key_len(char *env);
char			*get_env(t_data *data, char *new);
char			**init_envp(char **envp);
int				print_env_all(char **cmd, char **env);
void			print_env_sing(t_data *data, char *env);
int				print_env(char **env);
void			free_split(char **s);

/*              Lexing              */
int				lexing(t_data *data);
void			create_list(t_token **head, char *value, t_token_type type);
void			clearlist(t_token **head);
void			print_token_list(t_token *token_list);
void			print_arr(char **cmd);
t_token_type	check_char(char c);
char			*copy_part(char *input, int start, int len);
char			**split_string(char *input, int start, int len);
int				get_value_len(char *input, int i, t_token_type type);
void			check_syntax(t_token **head);

/*          Preparsing          */
void			count_ops(t_data *data);
void			preparsing(t_data *data);
void			delete_nullword(t_data *data, t_token **head);
void			replace_envvar(t_data *data);
int				list_size(t_token *head);
t_token			*cut_token(char	*s);
char			*reconnect(t_token **head);
void			replace_specialp(t_token **head, char **env);
char			*search_env(char *s, char **env);
void			store_cmd(t_token *start, t_token *end, int len);
int				check_dollar(char *s);
void			switch_value(t_token *token, char **env);
void			modify_cmd(t_data *data);
void			delete_rest(t_token *start, t_token *end);
void			delete_node(t_token **head, t_token *todelete);
void			handle_whitespaces(t_data *data, t_token **head);
void			delete_arg(t_token **head);

/*                Parsing             */
void			get_root(t_data *data);
t_node			*get_first_pipe(t_token *t_list);
t_node			*get_first_redir(t_token *t_list);
t_node			*create_node(t_token *token);
void			parsing(t_data *data);
void			build_left_branch(t_data *data, t_node *root, t_token *t_list);
void			build_right_branch(t_data *data, t_node *root, t_token *t_list);
void			free_ast(t_node *head);
int				ops_before_root(t_token *token_list);
t_token			*get_first_command(t_token *current);
t_token			*find_prev_op(t_token *token_list); // merge?
t_token			*find_next_op(t_token *token_list);
void			clear_table(t_data *data);

/*               Error               */
void			syntax_error(t_token **head, char c);
void			printf_error(char *str, int signal);
void			print_error_fd(const char *error, char *target);

/*              Delete              */
void            print_token(t_token *node);
void			print_node(t_node *node);
void			print_tree(t_node *node, int level);
const char		*get_token_type(t_token_type type);

#endif