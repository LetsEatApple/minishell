/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:01:04 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/13 12:50:41 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*check_path(char *cmd, char **path)
{
	char	*current_path;
	char	*command;
	int		i;

	command = ft_strjoin("/", cmd);
	i = 0;
	while (path[i])
	{
		current_path = ft_strjoin(path[i], command);
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

void	get_path(t_token *cmd, t_data *data)
{
	char	*path_env;
	char	**path;
	char	*cmd_path;
	int		len;
	char	*ptr;

	if (cmd->cmd[0][0] == '\0')
		return ;
	if (access(cmd->cmd[0], X_OK) == 0)
		return ;
	path_env = get_path_env(data->env);
	len = ft_strlen(path_env) - 5;
	path_env = ft_substr(path_env, 5, len);
	path = ft_split(path_env, ':');
	free(path_env);
	cmd_path = check_path(cmd->cmd[0], path);
	free_split(path);
	if (cmd_path == NULL)
		return ;
	ptr = cmd->cmd[0];
	cmd->cmd[0] = cmd_path;
	free(ptr);
}

void	modify_cmd(t_data *data)
{
	t_token	*ptr;

	ptr = data->token_list;
	while (ptr)
	{
		if (ptr->type == CMD)
			get_path(ptr, data);
		ptr = ptr->next;
	}
}
