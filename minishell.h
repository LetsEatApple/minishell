/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:21:45 by grmullin          #+#    #+#             */
/*   Updated: 2024/11/25 13:55:31 by grmullin         ###   ########.fr       */
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
# include "structs.h"
# include "Libft/libft.h"

char	**init_envp(char **envp);
void	free_data(t_data *data);
int	    init_data(t_data *data, int ac, char **envp);
void	handle_sig(int sig);
int     print_env(char **env);
void    free_split(char **s);

/*          Builtins            */
int     is_built_in(char *value);
int     ft_built_ins(t_data *data);

/*          Execution           */
int     ft_command(t_data *data);

#endif