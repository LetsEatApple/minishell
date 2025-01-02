/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:08:47 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/02 18:09:10 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	handle_redir_out(t_data *data, t_node *node)
{
	int	original_stdout;
	int	outfile;

	original_stdout = dup(STDOUT_FILENO);
	while (node->right->type == REDIR_OUT)
	{
		outfile = open(node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
		{
			printf_error("Error: Open: File could not be created\n", 1);
		}
		close(outfile);
		node->right = node->right->right;
	}
	outfile = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		printf_error("Error: Open: File could not be created\n", 1);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute(data, node->left);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

void	handle_redir_append(t_data *data, t_node *node)
{
	int	original_stdout;
	int	outfile;

	original_stdout = dup(STDOUT_FILENO);
	while (node->right->type == REDIR_OUT_APPEND)
	{
		outfile = open(node->right->left->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile < 0)
			perror("open error");
		close(outfile);
		node->right = node->right->right;
	}
	outfile = open(node->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile < 0)
		printf_error("Error: Open: File could not be created\n", 1);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute(data, node->left);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}
