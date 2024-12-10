/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:59:01 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/10 15:18:09 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int		i;
	t_token	*head;

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
