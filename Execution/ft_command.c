/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:59 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/13 13:00:11 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_command(char **cmd, char **env)
{
	/* if (is_built_in(data->token_list->cmd[0]))
		ft_built_ins(data->token_list->cmd[0]);
	else */
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
