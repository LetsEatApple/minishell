/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/09 16:34:38 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command(char *input, char **env)
{
	if (is_built_in(input))
		ft_built_ins(input);
	else
		ft_exec_command(input, env);
}

void	ft_exec_command(char *cmd, char **env)
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
}

void	ft_exec(char *path, char **args, char **env)
{
	if (execve(path, args, env) == -1)
		print_error("Execve error\n", 127);
}
