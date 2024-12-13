/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_later.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:48:08 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/13 13:20:27 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_node(t_node *node)
{
    if (node->cmd)
	{
		int i = 0;
		while (node->cmd[i])
		{
			printf("created node for '%s'\n", node->cmd[i]);
			i++;
		}
	}
	else
		printf("created node for '%s'\n", node->value);
}

void print_tree(t_node *node, int level)
{
	if (node == NULL)
		return;
	print_tree(node->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("Node Value: '%s', Type: %s\n", node->value, get_token_type(node->type));
	print_tree(node->left, level + 1);
}

const char *g_token_type[] = {
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
