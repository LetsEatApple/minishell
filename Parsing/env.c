/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:29:00 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/09 16:41:35 by lhagemos         ###   ########.fr       */
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
	int	i;
	int	size;
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
		//printf("token: %s und current env_var: %s\n", var, env[i]);
		if (strncmp(var, env[i], size-1) == 0)
		{
			value = ft_substr(env[i], size, len);
			break ;
		}
		i++;
	}
	free(var);
	return (value);
}

void	process_specialp(t_token **head, char *s, int *i)
{
	int		size;
	int		j;
	char	*sp;

	size = 0;
	j = *i;
	while (s[j])
	{
		if ((s[j] == '$' && j != *i) || s[j] == ' ' || s[j] == '\t')
			break ;
		size++;
		j++;
	}
	sp = copy_part(s, *i, size);
	create_list(head, sp, ENV);
	*i += size;
}

void	process_text(t_token **head, char *s, int *i)
{
	int		size;
	int		j;
	char	*text;

	size = 0;
	j = *i;
	while (s[j])
	{
		if (s[j] == '$')
			break ;
		size++;
		j++;
	}
	text = copy_part(s, *i, size);
	create_list(head, text, DOUBLE_QUOTE);
	*i += size;
}

t_token	*cut_quote(char	*s)
{
	int	i;
	t_token *head;

	i = 0;
	head = NULL;
	while (s[i])
	{
		if (s[i] == '$')
			process_specialp(&head, s, &i);
		if (s[i] != '\0' && s[i] != '$')
			process_text(&head, s, &i);
	}
	return (head);
}

void	replace_specialp(t_token **head, char **env)
{
	t_token	*ptr;
	char	*value;

	ptr = *head;
	while (ptr != NULL)
	{
		if (ptr->type == ENV && ft_strncmp("$", ptr->value, 2) != 0)
		{
			value = search_env(ptr->value, env);
			free(ptr->value);
			ptr->value = value;
		}
		ptr = ptr->next;
	}
}

char	*reconnect(t_token **head)
{
	char	*value;
	char	*temp;
	t_token	*ptr;

	ptr = *head;
	value = "";
	temp = "";
	while (ptr != NULL)
	{
		if (ptr->value != NULL)
		{
			temp = value;
			value = ft_strjoin(temp, ptr->value);
			if (temp[0] != '\0')
				free(temp);
		}
		ptr = ptr->next;
	}
	if (value[0] == '\0')
		value = NULL;
	return (value);
}

char	*modify_quote(char *s, char **env)
{
	t_token *head;
	char	*value;
	
	head = cut_quote(s);
	replace_specialp(&head, env);
	value = reconnect(&head);
	clearlist(&head);
	return (value);
}

void	switch_value(t_token *token, char **env)
{
	char *value;

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
	//t_token	*temp;

	ptr = data->token_list;
	while (ptr != NULL)
	{
		if (check_dollar(ptr->value) == true && ptr->type != SINGLE_QUOTE)
			switch_value(ptr, data->env);
		ptr = ptr->next;
	}
/* 	ptr = data->token_list;
	while (ptr != NULL)
	{
		if (ptr->type == WORD && ptr->value == NULL)
		{
			temp = ptr;
			ptr = ptr->next;
			deleteone(temp);
		}
		else
			ptr = ptr->next;
	} */
}