/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/23 17:56:33 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command(t_data *data, char **cmd)
{
	if (is_built_in(cmd[0]))
		ft_built_ins(data, cmd);
	else
	{
		g_signal = 0;
	//	if (S_ISDIR(cmd[0]))
		ft_exec(data, cmd);
	}
}

void	ft_exec(t_data *data, char **cmd)
{
	int		id;
	int		status;

	id = fork();
	if (id < 0)
		return ;
	if (id == 0)
	{
		if (execve(cmd[0], cmd, data->env) == -1)
		{
			print_error_fd("%s: command not found\n", cmd[0], 127);
			exit (g_signal);
		}
		clear_table(data);
		free_split(cmd);
		exit(g_signal);
	}
	dup2(data->std_out_fd, STDOUT_FILENO);
//	printf("adult\n");
	waitpid(id, &status, 0);
//	printf("child\n");
	//dup2(data->std_out_fd, STDOUT_FILENO);
	g_signal = WEXITSTATUS(status);
	return ;
}
