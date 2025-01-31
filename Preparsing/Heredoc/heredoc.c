/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:46:57 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/31 17:34:00 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_delimiter(t_node *node)
{
	char	*delimiter;

	if (node->prev == NULL && node->right->type == WORD)
		delimiter = node->right->value;
	else if (node->prev == NULL && node->right->left)
		delimiter = node->right->left->value;
	else if (node->right && node->right->type == WORD)
		delimiter = node->right->value;
	else if (node->left && node->left->type == WORD)
		delimiter = node->left->value;
	if (delimiter == NULL)
		return (NULL);
	return (delimiter);
}

t_node	*next_node(t_data *data, t_node *node, t_node *cmd)
{
	if (node->prev == NULL)
	{
		if (node->right->type >= 3 && node->right->type <= 6)
			return (node->right);
		else if (data->root->right->left->type == CMD)
			return (data->root->right->left);
	}
	else
	{
		if (node->prev->type != PIPE)
			return (node->prev);
		else if (node->prev->type == PIPE)
		{
			while (cmd && (cmd->type >= 3 && cmd->type <= 6))
			{
				if (cmd->left && cmd->left->type == CMD)
					break ;
				cmd = cmd->left;
			}
			return (cmd->left);
		}
	}
	return (node);
}

int	check_next_exec(t_data *data, t_node *node)
{
	t_node	*cmd;
	t_node	*next;

	cmd = data->root->left;
	if (data->pipes)
		next = next_node(data, node, cmd);
	else
	{
		if ((node->right == NULL || node->right->type == WORD)
			&& data->root->left)
			next = (data->root->left);
		else
			next = node->right;
	}
	if (node->type == HEREDOC || node->type == REDIR_IN)
	{
		if (next->type == CMD || next->type == 3 || next->type == 5)
			return (true);
	}
	else if (node->type == REDIR_OUT || node->type == REDIR_OUT_APPEND)
	{
		if (next->type == CMD || next->type == 4 || next->type == 6)
			return (true);
	}
	return (false);
}

void	handle_heredoc(t_data *data, t_node *node)
{
	data->doc.fd = open(data->doc.file, O_RDONLY);
	if (dup2(data->doc.fd, STDIN_FILENO) == -1)
	{
		close(data->doc.fd);
		ft_perror("dup21", 1);
		return ;
	}
	close(data->doc.fd);
	ft_next_exec(data, node);
}

void	init_heredoc(t_data *data)
{
	t_token	*ptr;

	ptr = data->token_list;
	while(ptr)
	{
		if (ptr->type == HEREDOC)
		{
			data->doc.delimiter = ptr->next->value;
			if (create_docfile(data, data->doc.delimiter) == false)
				break ;
		}
		ptr = ptr->next;
	}
}
