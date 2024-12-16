/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:11:11 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/13 16:04:12 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ops_before_root(t_token *token_list)
{
	int	ops;

	ops = 0;
	while (token_list && token_list->next)
	{
		if (token_list->node)
			break ;
		if (token_list->type > 1 && token_list->type < 7)
			ops++;
		token_list = token_list->next;
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
		if (current->node == 0 && (current->type > 1 
				&& current->type < 7))
			return (current);
		current = current->next;
	}
	return (NULL);
}
