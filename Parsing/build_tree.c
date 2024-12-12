/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:47:01 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/12 18:02:26 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*create_node(t_token *token)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	if (token->type != CMD)
	{
		new_node->cmd = NULL;
		new_node->value = ft_strdup(token->value);
	}
	else
	{
		new_node->value = NULL;
		new_node->cmd = token->cmd;
		token->cmd = NULL;
	}
	new_node->type = token->type;
	token->node = 1;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->node = 1;
	// if (new_node->cmd)
	// {
	// 	int i = 0;
	// 	while (new_node->cmd[i])
	// 	{
	// 		printf("created node for '%s'\n", new_node->cmd[i]);
	// 		i++;
	// 	}
	// }
	// else
	// 	printf("created node for '%s'\n", new_node->value);
	return (new_node);
}

void	build_ast(t_data *data, int ops)
{
	int	og_ops;

	og_ops = ops;
	if (ops > 0)
	{
//		printf("building left branch\n");
		ops = ops_before_root(data->token_list);
		build_left_branch(data->root, data->token_list, ops);
		ops = og_ops - ops;
	}
	build_right_branch(data->root, data->token_list, ops);
//	print_tree(data->root, 0);
}

void	build_right_branch(t_node *root, t_token *t_list, int ops)
{
	t_token	*current;
	t_token	*next_op;

	current = t_list;
	next_op = NULL;
//	printf("building right branch\n");
	while (current->node == 1)
		current = current->next;
	if (root->left == NULL)
	{
//		printf("root.left = '%s'\n", current->cmd[0]);
		root->left = create_node(current);
	}
	if (ops)
	{
		next_op = find_next_op(current);
		ops--;
		root->right = create_node(next_op);
		root->right->left = create_node(next_op->prev);
		build_right_branch(root->right, t_list, ops);
	}
	else
	{
		while (current->node == 1)
			current = current->next;
		root->right = create_node(current);
	}
}

void	build_left_branch(t_node *root, t_token *t_list, int ops)
{
	t_token	*current;
	t_token	*prev_op;

	current = t_list;
	prev_op = NULL;
	while (current->node == 0) //again why node?
		current = current->next;
	if (ops)
	{
		prev_op = find_prev_op(current);
		root->left = create_node(prev_op);
		root->left->right = create_node(prev_op->next);
		ops--;
		build_left_branch(root->left, t_list, ops);
	}
	else
		root->left = create_node(current->prev);
}
