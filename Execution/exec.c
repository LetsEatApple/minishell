/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:38:03 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/31 00:31:23 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_data *data, t_node *node)
{
	//printf("6file: %s\n", data->doc.file);
	if (node == NULL)
		return ;
	if (node->type == PIPE)
		handle_pipe(data, node);
	else if (node->type == REDIR_IN)
		handle_redir_in(data, node);
	else if (node->type == REDIR_OUT || node->type == REDIR_OUT_APPEND)
		handle_redir_out(data, node);
	else if (node->type == HEREDOC)
		handle_heredoc(data, node);
	else if (node->type == CMD)
		ft_command(data, node->cmd);
}

void	ft_next_exec(t_data *data, t_node *node)
{
	t_node	*cmd;

	cmd = data->root->left;
	if (data->pipes)
		pipes_exec(data, node, cmd);
	else
		no_pipes_exec(data, node);
}

void	pipes_exec(t_data *data, t_node *node, t_node *cmd)
{
	if (node->prev == NULL)
	{
		if (node->right->type >= 3 && node->right->type <= 6)
			execute(data, node->right);
		else if (data->root->right->left->type == CMD)
			execute(data, data->root->right->left);
	}
	else
	{
		if (node->prev->type != PIPE)
			execute(data, node->prev);
		else if (node->prev->type == PIPE)
		{
			while (cmd && (cmd->type >= 3 && cmd->type <= 6))
			{
				if (cmd->left && cmd->left->type == CMD)
					break ;
				cmd = cmd->left;
			}
			//error_msg("4,5file: %s\n", data->doc.file, g_signal);
			execute(data, cmd->left);
		}
	}
}

void	no_pipes_exec(t_data *data, t_node *node)
{
	if ((node->right == NULL || node->right->type == WORD) && data->root->left)
		execute(data, data->root->left);
	else
		execute(data, node->right);
}
