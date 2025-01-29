/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:20:45 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/29 16:40:21 by grmullin         ###   ########.fr       */
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
	data->ops = 0;
	data->root = NULL;
	data->doc.file = NULL;
	return (0);
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
