/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:11:11 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/19 13:14:12 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*get_first_command(t_token *current)
{
	if (current->type == CMD)
			return(current);
	else if (current->next->type == CMD)
			return(current->next);
	return (NULL);
}

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
		if (current->node == 0 && (current->type > 1 
				&& current->type < 7))
			return (current);
		current = current->next;
	}
	return (NULL);
}
