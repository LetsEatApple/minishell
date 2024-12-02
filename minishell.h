/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:21:45 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/02 14:17:30 by lhagemos         ###   ########.fr       */
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
# include "structs.h"
# include "Libft/libft.h"

extern volatile __sig_atomic_t	g_signal;

void	init_msh(t_data *data);
void	free_data(t_data *data);
int		init_data(t_data *data, int ac, char **envp);
void	handle_sig(int sig);
void    free_split(char **s);
int     is_whitespace(char c);
int		print_env(char **env);
void	free_split(char **s);

/*          Builtins            */
int 		is_built_in(char *value);
void		ft_built_ins(t_data *data);
int      ft_echo(t_data *data);

/*          Execution           */
void     ft_command(t_data *data);

/*          Env.vars            */
int     get_key_len(char *env);
char    *get_env(t_data *data, char *new);
char	**init_envp(char **envp);
int     print_env_all(char **env);
void    print_env_sing(t_data *data, char *env);
int		print_env(char **env);
void	free_split(char **s);


/*          Lexing              */
int				lexing(t_data *data);
void			create_list(t_token **head, char *value, t_token_type type);
void			clearlist(t_token **head);
void			free_splits(char **splits);
void			print_list(t_data *data);
t_token_type	check_char(char c);
char			*copy_part(char *input, int start, int len);
char			**split_string(char *input, int start, int len);
int				get_value_len(char *input, int i, t_token_type type);
void			check_syntax(t_token **head);


/*          Error               */
void	syntax_error(t_token **head, char c);

#endif