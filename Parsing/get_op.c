/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:24:42 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/28 17:39:07 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_root(t_data *data)
{
	if (data->pipes)
		data->root = get_first_pipe(data->token_list);
	if (data->redirs && data->root == NULL)
		data->root = get_first_redir(data->token_list);
}

t_node	*get_first_pipe(t_token *t_list) // fix here
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
		if (t_list->type == REDIR_IN || t_list->type == REDIR_OUT \
			|| t_list->type == REDIR_OUT_APPEND)
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
	return (NULL);
}

t_token	*get_first_command(t_token *real)
{
	t_token	*current;

	current = real;
	while (current && current->next)
	{
		if (current->node == 1)
			return (NULL);
		if (current->type == CMD && current->node == 0)
			return (current);
		else if (current->next->type == CMD && current->node == 0)
			return (current->next);
		current = current->next;
	}
	return (NULL);
}