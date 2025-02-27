/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:08:47 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/31 21:01:19 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redir_out(t_data *data, t_node *node)
{
	char	*outfile;

	outfile = get_outfile_redir_out(node);
	if (!outfile)
		return ;
	if (node->type == REDIR_OUT)
		data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		data->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (dup2(data->outfile, STDOUT_FILENO) < 0)
	{
		close(data->outfile);
		return (ft_perror("dup2", 1));
	}
	close(data->outfile);
	ft_next_exec(data, node);
}

char	*get_outfile_redir_out(t_node *node)
{
	char	*outfile;

	outfile = NULL;
	if (node->prev == NULL)
	{
		if (node->right->type == WORD)
			outfile = node->right->value;
		else if (node->right->left && node->right->left->type == CMD)
			outfile = node->left->value;
		else if (node->right->type == CMD)
			outfile = node->left->value;
		else
			outfile = node->right->left->value;
	}
	else if (node->left->type == WORD)
		outfile = node->left->value;
	else if (node->right->type == WORD)
		outfile = node->right->value;
	if (outfile == NULL)
		return (NULL);
	if (!check_file_validity(outfile, node->type))
		return (NULL);
	return (outfile);
}
