/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/29 08:35:31 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*left_redir_ins(t_node *node, t_token_type type)
{
	char	*infile;

	infile = node->right->value;
	while (node->left->type == type)
	{
		infile = node->left->right->value;
		if (!check_infile_validity(infile))
			return (NULL);
		node = node->left;
	}
	if (!check_infile_validity(node->right->value))
			return (NULL);
	return (infile);
}

char	*right_redir_ins(t_node *node, t_token_type type)
{
	char	*infile;

	infile = node->right->left->value;
	if (!check_infile_validity(infile))
		return (NULL);
	while (node->right->type == type)
	{
		infile = node->right->left->value;
		if (!check_infile_validity(infile))
			return (NULL);
		node = node->right;
	}
	infile = node->right->value;
	if (node->right->type != WORD)
		infile = node->right->left->value;
	return (infile);
}

char	*get_infile_red_in(t_data *data, t_node *node)
{
	char	*infile;
	(void)data;

	if (node->prev == NULL && node->right->type == WORD)
		infile = node->right->value;
	else if (node->prev == NULL)
		infile = node->right->left->value;	
	else if (node->right && node->right->type == WORD)
		infile = node->right->value;
	else if (node->left && node->left->type == WORD)
		infile = node->left->value;
	// else if (node->right && node->right->left->type == WORD)
	// 	infile = node->right->left->value;
	if (infile == NULL)
		return (NULL);
	if (!check_infile_validity(infile))
		return (NULL);
	// ft_putstr_fd(infile, 2);
	// printf("\n");
	return (infile);
}

t_node	*get_current(t_node *node, t_token_type type)
{
	if (node->left)
	{
		while (node->left->type == type)
			node = node->left;
	}
	if (node->right)
	{
		while (node->right->type == type)
			node = node->right;
	}
	return (node);
}

void	handle_redir_in(t_data *data, t_node *node)
{
	t_node	*current;
	char	*infile;
	int		original_stdin;
	
	current = node;
	if (!current)
		return ;
	infile = get_infile_red_in(data, node);
	if (infile == NULL )
		return ;
	data->infile = open(infile, O_RDONLY);
	original_stdin = dup(STDIN_FILENO);
	if (dup2(data->infile, STDIN_FILENO) == -1)
	{
		close(data->infile);
		ft_perror("dup2", 1);
		return ;
	}
	close(data->infile);
	if (data->pipes)
	{
		if (node->prev == NULL)
		{
			if (node->right->type >= 3 && node->right->type <= 6)
				execute(data, node->right);
			else if (data->root->right->left->type == CMD)
				execute(data, data->root->right->left);
		}
		else if (node->prev != NULL)
		{
			if (node->prev->type != PIPE)
				execute(data, node->prev);
			else if (node->prev->type == PIPE)
			{
				t_node *temp = data->root->left;
				while (temp && (temp->type >= 3 && temp->type <= 6))
				{
					if (temp->left && temp->left->type == CMD)
							break;
					temp = temp->left;
				}
				execute(data, temp->left);
			}
		}
	}
	else
	{
		if (node->right == NULL || node->right->type == WORD)
			execute(data, data->root->left);
		else
			execute(data, node->right);
	}
	if (dup2(original_stdin , STDIN_FILENO) == -1)
	{
		ft_perror("dup2", 1);
		return ;
	}
	close(original_stdin);
	// if (!data->pipes && current->right && current->right->type != WORD
	// 	&& current->right->type != HEREDOC)
	// {
	// 	if (current->right->type == 3 || current->right->type == 5)
	// 		outfile = get_outfile_redir_out(current->right);
	// 	if (!outfile)
	// 	{
	// 		dup2(original_stdin , STDIN_FILENO);
	// 		return ;
	// 	}
	// 	data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	if (dup2(data->outfile, STDOUT_FILENO) == -1)
	// 	{
	// 		perror("dup2");
	// 		return ;
	// 	}
	// 	close(data->outfile);
	// 	if (current->left->type == CMD)
	// 		execute(data, current->left);
	// 	else
	// 		execute(data, node->left);
	// 	dup2(data->std_out_fd , STDOUT_FILENO);
	// }
	// else
//	{
		// if (current->left && current->left->type == CMD)
		// 	execute(data, current->left);
		// else if(node->left && node->left->type == CMD)
		// 	execute(data, node->left);
//	}
//	data->std_in_fd = dup2(original_stdin , STDIN_FILENO);
	// close(original_stdin);
}
