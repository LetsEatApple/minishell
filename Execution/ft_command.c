/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/12 12:29:22 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command(t_data *data)
{
	/* if (is_built_in(data->token_list->cmd[0]))
		ft_built_ins(data->token_list->cmd[0]);
	else */
		ft_exec(data);
}



void	ft_exec(t_data *data)
{
	char	**args;
	int		id;

	id = fork();
	args = data->token_list->cmd;
	if (id < 0)
		return ;
	if (id == 0)
	{
		if (execve(args[0], args, data->env) == -1)
			printf("command not found: %s\n", args[0]);
		free_data(data);
		exit (4);
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