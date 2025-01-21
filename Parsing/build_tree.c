/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:47:01 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/21 16:04:48 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*create_node(t_token *token)
{
	t_node	*new_node;

	if (token == NULL)
		return (NULL);
	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	if (token->type != CMD)
	{
		new_node->cmd = NULL;
		new_node->value = token->value;
	}
	else	
	{
		new_node->value = NULL;
		new_node->cmd = token->cmd;
		token->cmd = NULL;
	}
	new_node->type = token->type;
	token->node = 1;
	new_node->node = 1;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	parsing(t_data *data)
{
	if (ops_before_root(data->token_list))
		build_left_branch(data, data->root, data->token_list);
	build_right_branch(data, data->root, data->token_list);
	// printf("\n");
	// print_tree(data->root, 0);
	// printf("\n");
}

void	build_right_branch(t_data *data, t_node *root, t_token *t_list)
{
	t_token	*current;
	t_token	*next_op;
	t_token	*first_cmd;

	current = t_list;
	next_op = NULL;
	first_cmd = NULL;
	while (current->node == 1)
		current = current->next;
	if (root->left == NULL)
	{
		first_cmd = get_first_command(t_list);
		if (first_cmd == NULL)
			root->left = create_node(NULL);
	}
	if (root->left == NULL)
		root->left = create_node(first_cmd);
	if (data->ops > 1)
	{
		next_op = find_next_op(current);
		if (!next_op && data->ops)
		{
			next_op = find_prev_op(current);
			data->ops--;
			root->left = create_node(next_op);
			if (redirs_between_pipes(t_list))
				root->right->left = create_node(redirs_between_pipes(t_list));
			else
				root->right->left = create_node(next_op->prev);
			build_right_branch(data, root->left, t_list);
		}
		else
		{
			data->ops--;
			root->right = create_node(next_op);
			if (redirs_between_pipes(t_list))
			{
				root->right->left = create_node(redirs_between_pipes(t_list));
				data->ops--;
				build_right_branch(data, root->right->left, t_list);		
			}
			else
				root->right->left = create_node(next_op->prev);
			build_right_branch(data, root->right, t_list);
		}
	}
	else
	{
		while (current->node == 1)
			current = current->next;
		root->right = create_node(current);
	}
}

void	build_left_branch(t_data *data, t_node *root, t_token *t_list)
{
	t_token	*current;
	t_token	*prev_op;

	current = t_list;
	prev_op = NULL;
	while (current->node == 0)
		current = current->next;
	if (ops_before_root(t_list))
	{
		prev_op = find_prev_op(current);
		root->left = create_node(prev_op);
		root->left->right = create_node(prev_op->next);
		data->ops--;
		build_left_branch(data, root->left, t_list);
	}
	else
	{
		if (current->prev)
			root->left = create_node(current->prev);
		else if (current->next->next
			&& current->next->next->type == CMD)
			root->left = create_node(current->next->next);
		else 
			return ;
	}
}
