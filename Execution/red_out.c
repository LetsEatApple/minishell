/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:43:10 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/26 20:42:26 by grmullin         ###   ########.fr       */
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
	// ft_putstr_fd("ret: ", 2);
	// ft_putstr_fd(outfile, 2);
	// ft_putstr_fd("\n", 2);
	if (!check_outfile_validity(outfile, REDIR_OUT))
		return (NULL);
	// ft_putstr_fd("ret: ", 2);
	// ft_putstr_fd(outfile, 2);
	// ft_putstr_fd("\n", 2);
	return (outfile);
}

char	*left_redir_out(t_node *node, t_token_type type)
{
	char	*outfile;

	outfile = node->right->value;
	if (!check_outfile_validity(outfile, type))
		return (NULL);
	while (node->left->type ==  3 || node->left->type == 5)
	{
		if (node->left->right->type == WORD)
			outfile = node->left->right->value;
		else if (node->right->left->right->type != WORD)
			outfile = node->left->left->value;
		if (!check_outfile_validity(outfile, node->left->type))
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
	// print_node(node);
	// print_node(node->right);
	// ft_putstr_fd("dale: ", 2);

	if (node->right->left->type == WORD)
	{
		outfile = node->right->left->value;
		if (!check_outfile_validity(outfile, type))
			return (NULL);		
	}
	// ft_putstr_fd("mewos\n", 2);
	// print_node(node);
	// print_node(node->right);
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
	// ft_putstr_fd("ret: ", 2);
	// ft_putstr_fd(outfile, 2);
	// ft_putstr_fd("\n", 2);
	return (outfile);
}
