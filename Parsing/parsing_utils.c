/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:11:11 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/04 13:02:14 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ops_before_root(t_token *token_list)
{
	int ops;

	ops = 0;
	while (token_list && token_list->next)
	{
		if (token_list->node)
			break;
		if (is_token_op(token_list))
			ops++;
		token_list = token_list->next;
	}
	printf("There are %d ops before the root\n", ops);
	return (ops);
}

int is_token_op(t_token *token)
{
	if (token->type == PIPE || token->type == REDIR_IN ||
		token->type == REDIR_OUT ||
		token->type == REDIR_OUT_APPEND ||
		token->type == HEREDOC)
			return (1);
	return (0);
}