/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/29 16:22:58 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command(t_data *data, char **cmd)
{
	struct stat	path;

	if ((cmd[0][0] == '.' || cmd[0][0] == '/'))
	{
		if (stat(cmd[0], &path) != 0)
			return (error_msg("%s: No such file or directory\n", cmd[0], 127));
		if (S_ISDIR(path.st_mode))
			return (error_msg("%s: Is a directory\n", cmd[0], 126));
		if (access(cmd[0], X_OK) == -1)
			return (error_msg("%s: Permission denied\n", cmd[0], 126));
	}
	if (is_built_in(cmd[0]))
		ft_built_ins(data, cmd);
	else
	{
		g_signal = 0;
		ft_exec(data, cmd);
	}
}

void	ft_exec(t_data *data, char **cmd)
{
	int		id;
	int		status;

	id = fork();
	if (id < 0)
	{
		perror("fork");
		return ;
	}
	if (id == 0)
	{
		if (execve(cmd[0], cmd, data->env) == -1)
		{
			error_msg("%s: command not found\n", cmd[0], 127);
			exit (g_signal);
		}
		clear_table(data);
		free_split(cmd);
		exit(g_signal);
	}
	waitpid(id, &status, 0);
	g_signal = WEXITSTATUS(status);
	return ;
}
