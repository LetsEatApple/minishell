/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/12 12:43:03 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command(char **cmd, char **env)
{
	/* if (is_built_in(data->token_list->cmd[0]))
		ft_built_ins(data->token_list->cmd[0]);
	else */
		ft_exec(cmd, env);
}



void	ft_exec(char **cmd, char **env)
{
	int		id;

	id = fork();
	if (id < 0)
		return ;
	if (id == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
			printf("command not found: %s\n", cmd[0]);
		free_split(env);
		free_split(cmd);
		exit (127);
	}
	wait(NULL);
	return ;
}

/* void	ft_exec_command(char *cmd, char **env)
{
	int		i;
	int		j;
	char	**split_paths;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			j = 0;
			split_paths = ft_split(env[i], ':');
			while (split_paths[j])
				ft_path_checker(split_paths[j++], cmd, env);
		}
		i++;
	}
	printf("%s: command not found\n", cmd);
	g_signal = 127;
}

void	ft_path_checker(char *paths, char *cmd, char **env)
{
	char	*correct;
	char	*full_path;
	char	**args;

	args = ft_split(cmd, ' ');
	correct = ft_strjoin(paths, "/");
	full_path = ft_strjoin(correct, args[0]);
	if (access(full_path, X_OK) == 0)
		ft_exec(full_path, args, env);
	free(correct);
	free(full_path);
	free(args);
} */