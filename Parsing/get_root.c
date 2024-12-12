/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:24:42 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/12 11:42:20 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_root(t_data *data)
{
	if (data->pipes)
	{
		data->root = get_first_pipe(data->token_list);
		data->pipes--; //what for?
	}
	if (data->redirs && data->root == NULL)
	{
		data->root = get_first_redir(data->token_list);
		data->redirs--; //what for?
	}
}

t_node	*get_first_pipe(t_token *t_list)
{
	while (t_list->next)
	{
		if (t_list->type == PIPE)
		{
			t_list->root = 1;
			return (create_node(t_list));
		}
		t_list = t_list->next;
	}
	return (NULL);
}

t_node	*get_first_redir(t_token *t_list)
{
	while (t_list->next)
	{
		if (t_list->type == REDIR_IN || t_list->type == REDIR_OUT \
			|| t_list->type == REDIR_OUT || t_list->type == HEREDOC)
		{
			t_list->root = 1;
			return (create_node(t_list));
		}
		t_list = t_list->next;
	}
	return (NULL);
}
