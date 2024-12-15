/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/15 14:12:22 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command(char **cmd, char **env)
{
	if (is_built_in(cmd[0]))
		ft_built_ins(cmd, env);
	else
		ft_exec(cmd, env);
}

void	ft_exec(char **cmd, char **env)
{
	int		id;

//	printf("about to exec '%s'\n", cmd[0]);
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
