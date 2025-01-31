/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:22:13 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/31 21:03:00 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	int	n;

	n = 0;
	g_signal = 0;
	if (ft_arrlen(cmd) > 1 && ft_strncmp(cmd[1], "-n", 3) == 0)
		n = 1;
	i = n +1;
	while (cmd[i] != NULL)
	{
		if (cmd[i][0] != '\0')
			printf("%s", cmd[i]);
		if (cmd[i +1] != NULL)
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
}

void	ft_pwd(t_data *data, char **cmd)
{
	g_signal = 0;
	if (ft_arrlen(cmd) != 1 && cmd[1][0] == '-')
	{
		error_msg("invalid option: %s\n", cmd[1], 2);
		return ;
	}
	if (data->pwd != NULL)
		printf("%s\n", data->pwd);
	else
		perror("getcwd:");
}

char	*get_home(t_env *head)
{
	t_env	*ptr;
	char	*home;

	ptr = head;
	home = NULL;
	while (ptr)
	{
		if (strncmp("HOME", ptr->var, 5) == 0)
		{
			home = ptr->value;
			break ;
		}
		ptr = ptr->next;
	}
	return (home);
}

char	*check_cd_args(t_data *data, char **cmd)
{
	char	*path;
	int		size;

	path = NULL;
	size = ft_arrlen(cmd);
	if (size == 1)
		path = get_home(data->e_list);
	else
		path = cmd[1];
	if (size > 2)
	{
		error_msg("%s: too many arguments\n", cmd[0], 1);
		return (NULL);
	}
	if (path == NULL || path[0] == '\0')
		return (NULL);
	return (path);
}

void	ft_cd(t_data *data, char **cmd)
{
	char	*path;

	g_signal = 0;
	path = check_cd_args(data, cmd);
	if (path == NULL)
		return ;
	if (chdir(path) < 0)
	{
		error_msg("cd: %s: ", path, 1);
		perror("");
	}
	path = getpwd();
	if (path == NULL)
		perror("cd: error retrieving current directory: \
			getcwd: cannot access parent directories");
	else
	{
		free(path);
		free(data->pwd);
		data->pwd = getpwd();
	}
}
