/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:22:13 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/18 15:50:06 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_built_ins(char **cmd, char **env)
{
	(void) env;
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return(ft_echo(cmd));
    // else if (ft_strncmp(s, "cd", 3) == 0)
    //     return (ft_cd(s)); // needs to be passed ENVP
    // else if (ft_strncmp(s, "pwd", 4) == 0)
    //     return (ft_pwd(s));
    // else if (ft_strncmp(s, "export", 7) == 0)
    //     return (ft_export(s));
    // else if (ft_strncmp(s, "unset", 6))
    //     return (ft_unset(node, envp));
	if (!ft_strncmp(cmd[0], "env", 4))
		return (print_env_all(cmd, env));
    //     return (ft_exit());
	return (0);
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
