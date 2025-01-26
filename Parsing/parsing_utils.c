/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:11:11 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/24 17:56:49 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ops_before_root(t_token *token_list)
{
	t_token	*list_copy;
	int		ops;

	list_copy = token_list;
	ops = 0;
	while (list_copy && list_copy->next)
	{
		if (list_copy->node)
			break ;
		if (list_copy->type > 1 && list_copy->type < 7)
			ops++;
		list_copy = list_copy->next;
	}
	return (ops);
}

t_token	*find_prev_op(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->node == 0 && (current->type > 1
				&& current->type < 7))
			return (current);
		current = current->prev;
	}
	return (NULL);
}

t_token	*find_next_op(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->node == 0 && current->type == PIPE)
			return (current);
		current = current->next;
	}
	current = token_list;
	while (current)
	{
		if (current->node == 0 && (current->type > 2 
				&& current->type < 7))
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_token	*redirs_between_pipes(t_token *t_list)
{
	t_token	*list_copy;
	int		first_pipe;

	list_copy = t_list;
	first_pipe = 0;
	while (list_copy && list_copy->next)
	{
		if (list_copy->type == PIPE && list_copy->node == 1)
			first_pipe = 1;
		if (first_pipe == 1)
		{
			list_copy = list_copy->next;
			while (list_copy->next)
			{
				if (list_copy->type == PIPE && list_copy->node == 1)
					return (find_prev_op(list_copy));
				list_copy = list_copy->next;
			}
		}
		list_copy = list_copy->next;
	}
	return (NULL);
}
