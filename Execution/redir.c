/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/02 18:20:49 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*left_redir_ins(t_node *node)
{
	int		fd;
	char	*infile;

	infile = node->right->value;
	while (node->left->type == REDIR_IN)
	{
		fd = open(node->left->right->value, O_RDONLY);
		if (fd == -1)
		{
			print_error_fd("bash: %s: No such file or directory\n", node->right->value);
			return (NULL);
		}
		close(fd);
		node = node->left;
	}
	fd = open(node->right->value, O_RDONLY);
	if (fd == -1)
	{
		print_error_fd("bash: %s: No such file or directory\n", node->right->value);
		return (NULL);
	}
	close(fd);
	return (infile);
}

char	*right_redir_ins(t_node *node)
{
	int		fd;
	char	*infile;

	infile = node->right->right->value;
	fd = open(node->right->left->value, O_RDONLY);
	if (fd == -1)
	{
		print_error_fd("bash: %s: No such file or directory\n", node->right->right->value);
		return (NULL);
	}
	close(fd);
	while (node->right->type == REDIR_IN)
	{
		fd = open(node->right->left->value, O_RDONLY);
		if (fd == -1)
		{
			printf("bash: %s: No such file or directory\n", node->right->left->value);
			return (NULL);
		}
		close(fd);
		infile = node->right->right->value;
		node = node->right;
	}
	return (infile);
}
// enters on '<'
char	*get_infile(t_node *node)
{
	char	*infile;
	int		fd;

	infile = node->right->value;
	if (node->left->type == REDIR_IN)
		infile = left_redir_ins(node);
	else if (node->right->type == REDIR_IN)
		infile = right_redir_ins(node);
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		printf("bash: %s: No such file or directory\n", infile);
		return (NULL);
	}
	close(fd);
	return (infile);
}

t_node	*get_current(t_node *node)
{
	while (node->left->type == REDIR_IN)
		node = node->left;
	while (node->right->type == REDIR_IN)
		node = node->right;
	return (node);
}

void	handle_redir_in(t_data *data, t_node *node)
{
	t_node	*current;
	int		original_stdin;
	int		infile;

	infile = 0;
	current = get_current(node);
	if (!current)
		return ;
	current->right->value = get_infile(node);
	infile = open(current->right->value, O_RDONLY);
	original_stdin = dup(STDIN_FILENO);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close(infile);
		return ;
	}
	close(infile);
	if (node->left->type == CMD)
		execute(data, node->left);
	else
		execute(data, current->left);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}
