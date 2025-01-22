/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:21:45 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/22 15:54:16 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
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

/*              Builtins            */
int				is_built_in(char *cmd);
void			ft_built_ins(t_data *data, char **cmd);
void			ft_echo(char **cmd);
int				ft_arrlen(char **cmd);
void			ft_pwd(t_data *data, char **cmd);
char			*getpwd(void);
void			ft_env(char **cmd, char **env);
void			ft_exit(t_data *data, char **cmd);
void			ft_export(t_data *data, char **cmd);
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
void			ft_unset(t_data *data, char **cmd);
void			ft_cd(t_data *data, char **cmd);

/*             Execution           */
void			ft_command(t_data *data, char **cmd);
void			execute(t_data *data, t_node *node);
void			handle_pipe(t_data *data, t_node *node);
void			dup_exec(int close_fd, int dup_fd, int std);
void			close_wait(int read, int write, pid_t left, pid_t right);
void			handle_redir_in(t_data *data, t_node *node);
void			handle_redir_out(t_data *data, t_node *node);
void			handle_redir_append(t_data *data, t_node *node);
void			handle_heredoc(t_data *data, t_node *node);
char			*ft_get_first_word(char *s);
int				check_for_infile(t_data *data, t_node *red_out);
void			ft_exec(t_data *data, char **cmd);
void			handle_two_tokens(t_data *data);
char			*left_redir_ins(t_node *node, t_token_type type);
char			*right_redir_ins(t_node *node, t_token_type type);
char			*get_infile_red_in(t_node *node);
char			*get_outfile_red_out(t_node *node);
char			*get_outfile_red_app(t_node *node);

// void			free_node(t_node *node);

/*              Env.vars            */
int				get_key_len(char *env);
char			*get_env(t_data *data, char *new);
char			**init_envp(char **envp);
void			free_split(char **s);

/*              Lexing              */
int				lexing(t_data *data);
void			create_list(t_token **head, char *value, t_token_type type);
void			clearlist(t_token **head);
void			print_token(t_token *token_list);
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
void			connect_val(t_token *ptr, t_token *start);

/*                Parsing             */
void			get_root(t_data *data);
t_node			*get_first_pipe(t_token *t_list);
t_node			*get_first_redir(t_token *t_list);
t_token			*redirs_between_pipes(t_token *t_list);
t_node			*create_node(t_token *new);
void			parsing(t_data *data);
void			build_left_branch(t_data *data, t_node *root, t_token *t_list);
void			build_right_branch(t_data *data, t_node *root, t_token *t_list);
void			free_ast(t_node *head);
int				ops_before_root(t_token *token_list);
t_token			*get_first_command(t_token *real);
t_token			*find_prev_op(t_token *token_list); // merge?
t_token			*find_next_op(t_token *token_list);
t_token			*get_prev_node(t_token *token);
void			clear_table(t_data *data);

/*               Error               */
void			syntax_error(t_token **head, char c);
void			printf_error(char *str, int signal);
void			print_error_fd(const char *error, char *target, int sig);

/*              Delete              */
void			print_token_list(t_token *token_list);
char			*print_node(t_node *node);
void			print_tree(t_node *node, int level);
const char		*get_token_type(t_token_type type);

#endif