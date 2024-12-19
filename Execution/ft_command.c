/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/19 14:41:59 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command(t_data *data, char **cmd)
{
	if (is_built_in(cmd[0]))
		ft_built_ins(data, cmd);
	else
		ft_exec(data, cmd);
}

void	ft_exec(t_data *data, char **cmd)
{
	int		id;

	id = fork();
	if (id < 0)
		return ;
	if (id == 0)
	{
		if (execve(cmd[0], cmd, data->env) == -1)
		{
			printf("%s: command not found\n", cmd[0]);
			exit (127);
		}
	}
	wait(NULL);
	return ;
}
