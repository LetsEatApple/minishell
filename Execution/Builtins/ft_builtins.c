/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:09:29 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/30 09:40:19 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_built_ins(t_data *data, char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ft_cd(data, cmd);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ft_pwd(data, cmd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		ft_export(data, cmd);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ft_unset(data, cmd);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		ft_env(cmd, data->env);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ft_exit(data, cmd);
	else
	{
		exec_command(data, cmd);
		g_signal = 127;
	}
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

int	ft_arrlen(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

char	*getpwd(void)
{
	char	*pwd;
	char	*save;
	char	buffer[PATH_MAX];

	save = getcwd(buffer, sizeof(buffer));
	if (save == NULL)
		return (NULL);
	pwd = ft_strdup(save);
	return (pwd);
}
