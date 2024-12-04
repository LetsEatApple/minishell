/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:47:01 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/04 17:07:21 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node *create_node(t_token *token)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	printf("creating node for: '%s'\n", token->value);
	if (new_node == NULL)
		return (NULL);
	new_node->value = ft_strdup(token->value);
	new_node->type = token->type;
	token->node = 1;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->node = 1;
	return (new_node);
}

// void	build_AST(t_data *data, int ops)
// {
// 	int og_ops;

// 	og_ops = ops;
// 	if (ops > 0)
// 	{
// 		ops = ops_before_root(data);
// 		build_left_branch(data->token_list, ops);
// 		data->root->node = 0;
// 		ops = og_ops - ops;
// 	}
// 	build_right_branch(data, ops);
// }

// void build_left_branch(t_data *data, int ops)
// {
// 	t_token	*current;
// 	t_token	*prev_op;
	
// 	prev_op = NULL;
// 	current = data->token_list;
// }