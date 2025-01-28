/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:43:10 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/27 14:35:24 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*get_outfile_redir_out(t_node *node)
{
	char	*outfile;

	if (node->right->type == WORD)
		outfile = node->right->value;
	else
		outfile = node->right->left->value;
	if (node->left && (node->left->type == 3 || node->left->type == 5))
		outfile = left_redir_out(node, node->left->type);
	else if (node->right && (node->right->type == 3 || node->right->type == 5))
		outfile = right_redir_out(node, node->right->type);
	if (outfile == NULL)
		return (NULL);
	if (!check_outfile_validity(outfile, REDIR_OUT))
		return (NULL);
	return (outfile);
}

char	*left_redir_out(t_node *node, t_token_type type)
{
	char	*outfile;
	char	*file;

	outfile = node->right->value;
	if (!check_outfile_validity(outfile, type))
		return (NULL);
	while (node->left->type ==  3 || node->left->type == 5)
	{
		if (node->left->right->type == WORD)
			file = node->left->right->value;
		else if (node->right->left->right->type != WORD)
			file = node->left->left->value;
		if (!check_outfile_validity(file, node->left->type))
			return (NULL);
		node = node->left;
	}
	if (!check_outfile_validity(node->right->value, type))
		return (NULL);
	return (outfile);
}

char	*right_redir_out(t_node *node, t_token_type type)
{
	char	*outfile;
	outfile = NULL;
	if (node->right->left->type == WORD)
	{
		outfile = node->right->left->value;
		if (!check_outfile_validity(outfile, type))
			return (NULL);		
	}
	while (node->right->type == 3 || node->right->type == 5)
	{
		if (node->right->left->type == WORD)
			outfile = node->right->left->value;
		else if (node->right->left->type != WORD)
			outfile = node->right->right->value;
		if (!check_outfile_validity(outfile, node->right->type))
			return (NULL);
		node = node->right;
	}
	outfile = node->right->value;
	if (node->right->type != WORD)
		outfile = node->right->left->value;
	if (!check_outfile_validity(outfile, type))
		return (NULL);
	return (outfile);
}
