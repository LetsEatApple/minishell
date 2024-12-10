/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:29:00 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/10 14:57:45 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*          check if token contains '$'           */
int	check_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char	*search_env(char *s, char **env)
{
	int		i;
	int		size;
	char	*value;
	char	*var;
	int		len;

	i = 0;
	size = ft_strlen(s);
	var = ft_substr(s, 1, size -1);
	value = NULL;
	while (env[i] != NULL)
	{
		len = ft_strlen(env[i]);
		if (strncmp(var, env[i], size -1) == 0)
		{
			value = ft_substr(env[i], size, len);
			break ;
		}
		i++;
	}
	free(var);
	return (value);
}

char	*modify_quote(char *s, char **env)
{
	t_token	*head;
	char	*value;

	head = cut_quote(s);
	replace_specialp(&head, env);
	value = reconnect(&head);
	clearlist(&head);
	return (value);
}

void	switch_value(t_token *token, char **env)
{
	char	*value;

	if (ft_strncmp("$", token->value, 2) == 0)
		return ;
	if (token->type != DOUBLE_QUOTE)
		value = search_env(token->value, env);
	else
		value = modify_quote(token->value, env);
	free(token->value);
	token->value = value;
	return ;
}

/*          searching for a $-token and replacing           */
void	replace_envvar(t_data *data)
{
	t_token	*ptr;

	ptr = data->token_list;
	while (ptr != NULL)
	{
		if (check_dollar(ptr->value) == true && ptr->type != SINGLE_QUOTE)
			switch_value(ptr, data->env);
		ptr = ptr->next;
	}
	delete_nullword(data, &data->token_list);
}
