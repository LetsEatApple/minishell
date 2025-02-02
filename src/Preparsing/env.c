/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:29:00 by lhagemos          #+#    #+#             */
/*   Updated: 2025/02/02 16:43:19 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*search_env(char *s, char **env)
{
	int		i;
	int		size;
	char	*value;
	char	*var;
	int		len;

	if (env == NULL)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	var = get_var_n_equals(s, size -1);
	value = NULL;
	while (env[i] != NULL)
	{
		len = ft_strlen(env[i]);
		if (ft_strncmp(var, env[i], size) == 0)
		{
			value = ft_substr(env[i], size, len);
			break ;
		}
		i++;
	}
	free(var);
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
