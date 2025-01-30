/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:20:45 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/30 23:10:38 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_data(t_data *data, int ac, char **envp)
{
	if (ac != 1)
		return (0);
	data->input = NULL;
	data->env = init_envp(envp);
	data->e_list = arr2list(data);
	data->pwd = getpwd();
	data->token_list = NULL;
	data->pipes = 0;
	data->redirs = 0;
	data->red_in = 0;
	data->heredoc = 0;
	data->infile = -1;
	data->outfile = -1;
	data->stdin = dup(STDIN_FILENO);
	data->stdout = dup(STDOUT_FILENO);
	data->ops = 0;
	data->root = NULL;
	data->doc.file = NULL;
	return (0);
}

int	restore_std(t_data *data, char option)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (option == 0 || option == 2)
		dup2(data->stdin, STDIN_FILENO);
	if (option == 1 || option == 2)
		dup2(data->stdout, STDOUT_FILENO);
	return (1);
}

char	**init_envp(char **envp)
{
	char	**list_env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	list_env = malloc(sizeof(char *) * (i + 1));
	if (!list_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		list_env[i] = ft_strdup(envp[i]);
		i++;
	}
	list_env[i] = NULL;
	return (list_env);
}
