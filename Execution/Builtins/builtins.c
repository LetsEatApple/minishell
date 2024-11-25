/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:22:13 by grmullin          #+#    #+#             */
/*   Updated: 2024/11/25 13:55:22 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    ft_command(t_data *data)
{
 //   printf("in ft_command w: '%s'\n", node->value);
    if (is_built_in(data->input))
        ft_built_ins(data);
    // else if (ft_exec_command(node, envp) == 0)
    //     return (0);
    else
    {
        printf("%s: command not found\n", data->input);
        return (127);
    }
    return (0);
}

int    ft_built_ins(t_data *data)
{
    // if (ft_strncmp(s, "echo", 4) == 0)
    //     return (ft_echo(s));
    // else if (ft_strncmp(s, "cd", 2) == 0)
    //     return (ft_cd(s)); // needs to be passed ENVP 
    // else if (ft_strncmp(s, "pwd", 3) == 0)
    //     return (ft_pwd(s));
    // else if (ft_strncmp(s, "export", 6) == 0)
    //     return (ft_export(s));
    // else if (ft_strncmp(s, "unset", 5))
    //     return (ft_unset(node, envp));
    if (!ft_strncmp(data->input, "env", 3))
        return (print_env(data->env));
    // else if (ft_strncmp(s, "exit", 4))
    //     return (ft_exit());
    return (0);
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

void    free_split(char **s)
{
    int i;

    i = 0;
    while (s[i])
    {
        free(s[i]);
        i++;
    }
    free(s);
}