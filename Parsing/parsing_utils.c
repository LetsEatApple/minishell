/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:11:11 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/09 10:17:11 by grmullin         ###   ########.fr       */
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
		if (is_token_op(token_list))
			ops++;
		token_list = token_list->next;
	}
	return (ops);
}

int	is_token_op(t_token *token)
{
	if (token->type == PIPE || token->type == REDIR_IN
		|| token->type == REDIR_OUT || token->type == REDIR_OUT_APPEND
		|| token->type == HEREDOC)
		return (1);
	return (0);
}

t_token	*find_prev_op(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (is_token_op(current) && current->node == 0)
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
		if (is_token_op(current) && current->node == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
