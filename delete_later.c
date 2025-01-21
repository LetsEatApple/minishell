/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_later.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:48:08 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/21 16:39:27 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_node(t_node *node)
{
	if (node->cmd)
	{
		// int i = 0;
		// while (node->cmd[i])
		// {
		// 	printf("cmd node is'%s'\n", node->cmd[i]);
		// 	i++;
		// }
	//	ft_putstr_fd("cmd is ", 2);
		ft_putstr_fd(node->cmd[0], 2);
		ft_putstr_fd("\n", 2);
		return (node->cmd[0]);
	}
	else
	{
	//	ft_putstr_fd("node is ", 2);
		ft_putstr_fd(node->value, 2);
		ft_putstr_fd("\n", 2);
	}
	return (node->value);
}

void    print_token(t_token *node)
{
    if (node->cmd)
	{
		int i = 0;
		while (node->cmd[i])
		{
			printf("token is '%s' type '%s'\n", node->cmd[i], get_token_type(node->type));;
			i++;
		}
	}
	else
		printf("token is '%s' type '%s'\n", node->value, get_token_type(node->type));;
}

void print_tree(t_node *node, int level)
{
	if (node == NULL)
		return;
	print_tree(node->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("    ");
	if (node->value)
		printf("Node Value: '%s', Type: %s\n", node->value, get_token_type(node->type));
	else if (node->cmd)
		printf("Node Value: '%s', Type: %s\n", node->cmd[0], get_token_type(node->type));
	print_tree(node->left, level + 1);
}

const char *g_token_type[] = 
{
    "SINGLE_QUOTE",
    "DOUBLE_QUOTE",
    "PIPE",
    "REDIR_OUT",
    "REDIR_IN",
    "REDIR_OUT_APPEND",
    "HEREDOC",
    "WORD",
	"CMD",
    "ENV",
};

const char* get_token_type(t_token_type type) {
    if (type >= 0 && type <= ENV)  // Ensure the type is within valid range
        return g_token_type[type];
    return "UNKNOWN";  // Fallback for invalid types
}
