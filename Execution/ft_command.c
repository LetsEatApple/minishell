/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/31 01:20:02 by lhagemos         ###   ########.fr       */
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
		exec_command(data, cmd);
	}
}

void	exec_command(t_data *data, char **cmd)
{
	int		id;
	int		status;

	id = fork();
	if (id < 0)
		return (ft_perror("fork", 1));
	if (id == 0)
	{
		close(data->stdin);
		close(data->stdout);
		if (execve(cmd[0], cmd, data->env) == -1)
		{
			error_msg("%s: command not found\n", cmd[0], 127);
			exit (g_signal);
		}
		// clear_table(data);
		// free_split(cmd);
		// exit(g_signal);    if these lines delted norm=ok , do we need them?
	}
	restore_std(data, 2);
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		g_signal = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		g_signal = 128 + WTERMSIG(status);
	}
}
