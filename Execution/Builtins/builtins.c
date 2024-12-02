/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:22:13 by grmullin          #+#    #+#             */
/*   Updated: 2024/11/28 15:57:56 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_built_ins(t_data *data)
{
    if (ft_strncmp(data->input, "echo", 4) == 0)
        ft_echo(data);
    // else if (ft_strncmp(s, "cd", 2) == 0)
    //     return (ft_cd(s)); // needs to be passed ENVP 
    // else if (ft_strncmp(s, "pwd", 3) == 0)
    //     return (ft_pwd(s));
    // else if (ft_strncmp(s, "export", 6) == 0)
    //     return (ft_export(s));
    // else if (ft_strncmp(s, "unset", 5))
    //     return (ft_unset(node, envp));
    if (!ft_strncmp(data->input, "env", 3))
        print_env_all(data->env);
    // else if (ft_strncmp(s, "exit", 4))
    //     return (ft_exit());
}

int is_built_in(char *value)
{
    const char  *builtins[] = \
    {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    char        **s;
    int         i;

    i = 0;
    s = ft_split(value, ' ');
    while (i < 7)
    {
        if (ft_strncmp(s[0], builtins[i], ft_strlen(builtins[i])) == 0)
        {
            free_split(s);
            return (1);
        }
        i++;
    }
    free_split(s);
    return (0);
}
