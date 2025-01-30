/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:47:01 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/30 14:28:16 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(t_data *data)
{
	if (ops_before_root(data->token_list))
		build_left_branch(data, data->root, data->token_list);
	build_right_branch(data, data->root, data->token_list);
}

void	build_right_branch(t_data *data, t_node *root, t_token *t_list)
{
	t_token	*current;
	t_token	*next_op;

	current = t_list;
	next_op = NULL;
	while (current->next && current->node == 1)
		current = current->next;
	if (root->left == NULL)
		root->left = create_node(get_first_command(t_list), NULL);
	if (data->ops > 1)
	{
		next_op = find_next_op(current);
		if (!next_op && data->ops)
			prev_op_branch(data, current);
		else
			next_op_branch(data, root, next_op);
	}
	else
	{
		while (current->next && current->node == 1)
			current = current->next;
		root->right = create_node(current, NULL);
	}
}

void	next_op_branch(t_data *data, t_node *root, t_token *next_op)
{
	t_token	*redir;

	redir = redirs_between_pipes(data->token_list);
	data->ops--;
	root->right = create_node(next_op, NULL);
	if (redir != NULL)
	{
		root->right->left = create_node(redir, NULL);
		data->ops--;
		build_right_branch(data, root->right->left, data->token_list);
	}
	else
		root->right->left = create_node(get_command(next_op), NULL);
	build_right_branch(data, root->right, data->token_list);
}

void	prev_op_branch(t_data *data, t_token *current)
{
	t_token	*prev_op;
	t_token	*redir;

	redir = redirs_between_pipes(data->token_list);
	prev_op = find_prev_op(current);
	data->ops--;
	data->root->left = create_node(prev_op, NULL);
	if (redir != NULL)
		data->root->right->left = create_node(redir, NULL);
	else
		data->root->right->left = create_node(prev_op->prev, NULL);
	build_right_branch(data, data->root->left, data->token_list);
}

void	build_left_branch(t_data *data, t_node *root, t_token *t_list)
{
	t_token	*current;
	t_token	*prev_op;

	current = t_list;
	prev_op = NULL;
	while (current && current->node == 0)
		current = current->next;
	if (ops_before_root(t_list))
	{
		prev_op = find_prev_op(current);
		root->left = create_node(prev_op, root);
		root->left->right = create_node(prev_op->next, root->left);
		data->ops--;
		build_left_branch(data, root->left, t_list);
	}
	else
	{
		if (current->prev)
			root->left = create_node(current->prev, root);
		else if (current->next->next
			&& current->next->next->type == CMD)
			root->left = create_node(current->next->next, root);
		else 
			return ;
	}
}
