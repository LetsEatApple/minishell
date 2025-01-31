/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:24:42 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/31 21:01:19 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_root(t_data *data)
{
	if (data->pipes)
		data->root = get_first_pipe(data->token_list);
	if (data->redirs && data->root == NULL)
		data->root = get_first_redir(data->token_list);
}

t_node	*get_first_pipe(t_token *t_list)
{
	t_node	*new_node;

	while (t_list->next)
	{
		if (t_list->type == PIPE)
		{
			t_list->root = 1;
			new_node = create_node(t_list, NULL);
			return (new_node);
		}
		t_list = t_list->next;
	}
	return (NULL);
}

t_node	*get_first_redir(t_token *t_list)
{
	t_node	*new_node;

	while (t_list->next)
	{
		if (t_list->type > 2 && t_list->type < 7)
		{
			t_list->root = 1;
			new_node = create_node(t_list, NULL);
			return (new_node);
		}
		t_list = t_list->next;
	}
	return (NULL);
}

t_token	*get_command(t_token *token)
{
	if (token->prev->type == WORD || token->prev->type == CMD)
		return (token->prev);
	else if (token->next->type == CMD || token->next->type == WORD)
		return (token->next);
	else if (token->next->next->type == CMD)
		return (token->next->next);
	return (NULL);
}

t_token	*get_first_command(t_token *real)
{
	t_token	*current;

	current = real;
	while (current && current->next)
	{
		if (current->type == CMD && current->node == 0)
			return (current);
		else if (current->next->type == CMD && current->node == 0)
			return (current->next);
		else if (current->prev && current->prev->type == CMD)
			return (current->prev);
		current = current->next;
	}
	return (NULL);
}
