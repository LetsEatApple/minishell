/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:26:29 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/15 12:50:22 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_next(t_token *token)
{
	t_token *current;

	current = token->prev;
	while (token && token->type == WHITESPACE)
		token = token->next;
	if (token == NULL)
		return (false);
	if (current->type != PIPE)
	{
		if (token->type != WORD && token->type != SINGLE_QUOTE
		&& token->type != DOUBLE_QUOTE)
		return (false);
	}
	return (true);
}

int	valid_prev(t_token *token)
{
	while (token && token->type == WHITESPACE)
		token = token->prev;
	if (token == NULL)
		return (false);
	if (token->type == PIPE)
		return (false);
	/* if (token->type != WORD && token->type != SINGLE_QUOTE
		&& token->type != DOUBLE_QUOTE)
		return (false); */
	return (true);
}

void	check_syntax(t_token **head)
{
	t_token	*ptr;

	if (head == NULL)
		return ;
	ptr = *head;
	while (ptr)
	{
		if (ptr->type > 1 && ptr->type < 7)
		{
			if (valid_next(ptr->next) == false)
			{
				syntax_error(head, ptr->value[0]);
				return ;
			}
			if (ptr->type == PIPE && valid_prev(ptr->prev) == false)
			{
				syntax_error(head, ptr->value[0]);
				return ;
			}
		}
		ptr = ptr->next;
	}
}
