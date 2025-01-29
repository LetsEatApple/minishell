/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:08:47 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/29 08:35:59 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redir_out(t_data *data, t_node *node)
{
	t_node	*current;

	current = get_current(node, node->type);
	current->right->value = get_outfile_redir_out(node);
	if (!current->right->value)
		return ;
	data->outfile = open(current->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(data->outfile, STDOUT_FILENO) < 0)
	{
		close(data->outfile);
		ft_perror("dup2", 1);
		return ;
	}
	close(data->outfile);
	if (check_for_infile(data, node))
		return ;
	if (node->left)
		execute(data, node->left);
	if (data->std_out_fd >= 0)
	{
		if (dup2(data->std_out_fd, STDOUT_FILENO) < 0)
		{
			ft_perror("dup2", 1);
			return ;
		}
	}
}

void	handle_redir_append(t_data *data, t_node *node)
{
	t_node	*current;

	current = get_current(node, node->type);
	current->right->value = get_outfile_redir_out(node);
	if (!current->right->value)
	{
		g_signal = 1;
		return ;
	}
	data->outfile = open(current->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
	{
		close(data->outfile);
		ft_perror("dup2", 1);
		return ;
	}
	close(data->outfile);
	if (check_for_infile(data, node))
		return ;
	if (node->left)
		execute(data, node->left);
	if (data->std_out_fd >= 0)
	{
		if (dup2(data->std_out_fd, STDOUT_FILENO) < 0)
		{
			ft_perror("dup2", 1);
			return ;
		}
	}
}
