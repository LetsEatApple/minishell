/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:22:13 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/05 22:34:31 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char **cmd)
{
	int	i;
	int	n;

	n = 0;
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
	return (0);
}

int	ft_pwd(t_data *data, char **cmd)
{
	if (ft_arrlen(cmd) != 1 && cmd[1][0] == '-')
	{
		print_error_fd("invalid option: %s\n", cmd[1]);
		return (2);
	}
	if (data->pwd != NULL) 
		printf("%s\n", data->pwd);
	else
	{
		perror("getcwd failed");
		return (1);
	}
	return (0);
}

int	print_env_all(char **cmd, char **env)
{
	int	i;

	if (ft_arrlen(cmd) != 1)
	{
		print_error_fd("invalid argument/option: %s\n", cmd[1]);
		return (2); // adjust value 125/127
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

char	*get_home(t_env *head)
{
	t_env	*ptr;
	char	*home;

	ptr = head;
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

int	ft_cd(t_data *data, char **cmd)
{
	int		size;
	char	*path;
	
	size = ft_arrlen(cmd);
	if (size == 1)
		path = get_home(data->e_list);
	else
		path = cmd[1];
	if (size > 2)
	{
		print_error_fd("%s: too many arguments\n", cmd[0]);
		return (1);
	}
	if (path == NULL || path[0] == '\0')
		return (0);
	if (chdir(path) < 0)
		print_error_fd("%s: No such file or directory\n", path);
	free(data->pwd);
	data->pwd = getpwd();
	return 0;
}
