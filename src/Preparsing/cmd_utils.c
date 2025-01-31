/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:06:06 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/31 20:58:16 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_rest(t_token *start, t_token *end)
{
	t_token	*ptr;

	ptr = start->next;
	while (ptr != end)
	{
		if (ptr->value != NULL)
			free(ptr->value);
		if (ptr->next == NULL)
		{
			free(ptr);
			break ;
		}
		ptr = ptr->next;
		free(ptr->prev);
	}
	start->next = end;
	if (end != NULL)
		end->prev = start;
}

void	delete_arg(t_token **head)
{
	t_token	*ptr;

	ptr = *head;
	while (ptr)
	{
		if (ptr->arg == 1)
		{
			delete_node(head, ptr);
			ptr = *head;
		}
		else
			ptr = ptr->next;
	}
}

void	store_cmd(t_token *start, t_token *end, int len)
{
	t_token	*ptr;
	char	**cmd;
	int		i;

	cmd = (char **)malloc((len +1) * sizeof(char *));
	ptr = start;
	i = 0;
	while (ptr != end)
	{
		if (ptr->arg == 1)
		{
			if (ptr->value == NULL)
				ptr->value = ft_strdup("");
			cmd[i] = ft_strdup(ptr->value);
			i++;
		}
		ptr = ptr->next;
	}
	cmd[i] = NULL;
	free(start->value);
	start->value = NULL;
	start->cmd = cmd;
	start->type = CMD;
	start->arg = 0;
}
