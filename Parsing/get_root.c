/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:24:42 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/09 10:18:27 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_root(t_data *data)
{
	if (data->pipes)
	{
		data->root = get_first_pipe(data->token_list);
		data->pipes--;
	}
	if (data->redirs && data->root == NULL)
	{
		data->root = get_first_redir(data->token_list);
		data->redirs--;
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
