/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_later.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:48:08 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/30 14:30:19 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_node(t_node *node)
{
	if (node->cmd)
	{
		ft_putstr_fd(node->cmd[0], 2);
		ft_putstr_fd("\n", 2);
		return (node->cmd[0]);
	}
	else if (node->value)
	{
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
		ft_putstr_fd("    ", 2);
	if (node->value)
	{
		ft_putstr_fd("Node Value: '", 2);
		ft_putstr_fd(node->value, 2);
		ft_putstr_fd("', Type: ", 2);
		ft_putstr_fd((char *)get_token_type(node->type), 2);
		ft_putstr_fd("\n", 2);
	}
	else if (node->cmd)
	{
		ft_putstr_fd("Node Value: '", 2);
		ft_putstr_fd(node->cmd[0], 2);
		ft_putstr_fd("', Type: ", 2);
		ft_putstr_fd((char *)get_token_type(node->type), 2);
		ft_putstr_fd("\n", 2);
	}
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
    if (type >= 0 && type <= ENV)
        return g_token_type[type];
    return "UNKNOWN";
}
