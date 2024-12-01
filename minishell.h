/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:21:45 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/01 14:53:37 by lhagemos         ###   ########.fr       */
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

char	**init_envp(char **envp);
void	free_data(t_data *data);
int		init_data(t_data *data, int ac, char **envp);
void	handle_sig(int sig);
int		print_env(char **env);
void	free_split(char **s);

/*          Builtins            */
int		is_built_in(char *value);
int		ft_built_ins(t_data *data);

/*          Execution           */
int		ft_command(t_data *data);

/*          Lexing              */
int				lexing(char *input);
void			create_list(t_token **head, char *value, t_token_type type);
void			clearlist(t_token **head);
void			free_splits(char **splits);
void			print_list(t_token **head);
t_token_type	check_char(char c);
char			*copy_part(char *input, int start, int len);
char			**split_string(char *input, int start, int len);
int				get_value_len(char *input, int i, t_token_type type);
void			check_syntax(t_token **head);


/*          Error               */
void	syntax_error(t_token **head, char c);

#endif