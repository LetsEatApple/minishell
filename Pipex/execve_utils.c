/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:15:28 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/08 09:36:47 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (env[i]);
}

char	*check_path(t_pro *pipex, int cmd)
{
	char	*current_path;
	char	*command;
	int		i;

	if (cmd == 1)
		command = ft_strjoin("/", pipex->cmd1[0]);
	else
		command = ft_strjoin("/", pipex->cmd2[0]);
	i = 0;
	while (pipex->path[i])
	{
		current_path = ft_strjoin(pipex->path[i], command);
		if (access(current_path, F_OK) == 0)
		{
			free(command);
			return (current_path);
		}
		free(current_path);
		i++;
	}
	free(command);
	return (NULL);
}

void	get_cmd1_path(t_pro *pipex)
{
	char	*cmd_path;
	char	*ptr;

	cmd_path = check_path(pipex, 1);
	if (cmd_path == NULL)
		return ;
	ptr = pipex->cmd1[0];
	pipex->cmd1[0] = cmd_path;
	free(ptr);
}

void	get_cmd2_path(t_pro *pipex)
{
	char	*cmd_path;
	char	*ptr;

	cmd_path = check_path(pipex, 2);
	if (cmd_path == NULL)
		return ;
	ptr = pipex->cmd2[0];
	pipex->cmd2[0] = cmd_path;
	free(ptr);
}
