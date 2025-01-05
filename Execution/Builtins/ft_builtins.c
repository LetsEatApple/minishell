/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:09:29 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/05 22:34:51 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_built_ins(t_data *data, char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return(ft_echo(cmd));
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (ft_cd(data, cmd));
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (ft_pwd(data, cmd));
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (ft_export(data, cmd));
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (ft_unset(data, cmd));
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (print_env_all(cmd, data->env));
	if(!ft_strncmp(cmd[0], "exit", 5))
		return(ft_exit(data, cmd));
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

int	ft_arrlen(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

char	*getpwd()
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
