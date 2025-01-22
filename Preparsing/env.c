/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:29:00 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/22 13:38:51 by lhagemos         ###   ########.fr       */
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
	char	*tmp;
	int		len;

	i = 0;
	size = ft_strlen(s);
	var = ft_substr(s, 1, size -1);
	tmp = var;
	var = ft_strjoin(var, "=");
	value = NULL;
	while (env[i] != NULL)
	{
		len = ft_strlen(env[i]);
		if (strncmp(var, env[i], size) == 0)
		{
			value = ft_substr(env[i], size, len);
			break ;
		}
		i++;
	}
	free(var);
	free(tmp);
	return (value);
}

void	replace_specialp(t_token **head, char **env)
{
	t_token	*ptr;
	char	*value;

	ptr = *head;
	while (ptr)
	{
		if (ptr->type == ENV && ft_strncmp("$", ptr->value, 2) != 0)
		{
			if (ft_strncmp(ptr->value, "$?", 3) == 0)
				value = ft_itoa(g_signal);
			else
				value = search_env(ptr->value, env);
			free(ptr->value);
			ptr->value = value;
		}
		ptr = ptr->next;
	}
}

char	*modify_token(char *s, char **env)
{
	t_token	*head;
	char	*value;

	head = cut_token(s);
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
	value = modify_token(token->value, env);
	free(token->value);
	token->value = value;
	return ;
}
