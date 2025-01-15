/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/14 13:48:31 by lhagemos         ###   ########.fr       */
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
			printf("%s: command not found\n", cmd[0]);
			g_signal = 127;
			exit (g_signal);
		}
		clear_table(data);
		free_split(cmd);
		exit(g_signal); //exit(EXIT_SUCCESS); ????
	}
	waitpid(id, &status, 0);
	g_signal = WEXITSTATUS(status);
	//wait(NULL);
	return ;
}
