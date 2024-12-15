/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:22:13 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/12 20:11:12 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_built_ins(char **cmd, char **env)
{
	(void) env;
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		ft_echo(cmd);
    // else if (ft_strncmp(s, "cd", 2) == 0)
    //     return (ft_cd(s)); // needs to be passed ENVP
    // else if (ft_strncmp(s, "pwd", 3) == 0)
    //     return (ft_pwd(s));
    // else if (ft_strncmp(s, "export", 6) == 0)
    //     return (ft_export(s));
    // else if (ft_strncmp(s, "unset", 5))
    //     return (ft_unset(node, envp));
    // if (!ft_strncmp(data->input, "env", 3))
    //     print_env_all(data->env);
    // else if (ft_strncmp(s, "exit", 4))
    //     return (ft_exit());
}

int	is_built_in(char *cmd)
{
	const char	*builtins[] = \
	{"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}
