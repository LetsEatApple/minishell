/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:22:13 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/23 16:30:45 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		print_error_fd("invalid option: %s\n", cmd[1], 2);
		return ;
	}
	if (data->pwd != NULL)
		printf("%s\n", data->pwd);
	else
		perror("getcwd:");
}

//env in bash returns 125/127 but is not a builtin there
//should we choose 2 instead (Misuse of Shell Builtin)?
void	ft_env(char **cmd, char **env)
{
	int	i;

	g_signal = 0;
	if (ft_arrlen(cmd) != 1)
	{
		if (cmd[1][0] == '-')
			print_error_fd("env: invalid option: %s\n", cmd[1], 125);
		else
			print_error_fd("env: invalid argument: %s\n", cmd[1], 127);
		return ;
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
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

void	ft_cd(t_data *data, char **cmd)
{
	int		size;
	char	*path;

	g_signal = 0;
	size = ft_arrlen(cmd);
	if (size == 1)
		path = get_home(data->e_list);
	else
		path = cmd[1];
	if (size > 2)
	{
		print_error_fd("%s: too many arguments\n", cmd[0], 1);
		return ;
	}
	if (path == NULL || path[0] == '\0')
		return ;
	if (chdir(path) < 0)
	{
		print_error_fd("cd: %s: ", path, 1);
		perror("");
	}
	path = getpwd();
	if (path == NULL)
		perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
	else
	{
		free(path);
		free(data->pwd);
		data->pwd = getpwd();
	}
}
