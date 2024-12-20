/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:53:44 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/18 15:29:23 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env_all(char **cmd, char **env)
{
	int	i;

	if (ft_arrlen(cmd) != 1)
	{
		print_err("invalid argument/option: %s\n", cmd[1]);
		return (0); // adjust value
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

void	print_env_sing(t_data *data, char *env)
{
	char	*key;
	char	*value;
	int		key_len;
	int		value_len;
	int		i;

	key = NULL;
	value = NULL;
	i = 0;
	while (!is_whitespace(env[i]))
		i++;
	key = ft_substr(env, 1, i - 1);
	key_len = ft_strlen(key);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(key, data->env[i], key_len) == 0)
			break ;
		i++;
	}
	value_len = ft_strlen(data->env[i]) - key_len;
	value = ft_substr(data->env[i], key_len + 1, value_len);
	ft_putstr_fd(value, 1);
	free (key);
	free (value);
}
