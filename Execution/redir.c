/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/08 19:58:31 by grmullin         ###   ########.fr       */
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
			perror(node->left->right->value);
			return (NULL);
		}
		close(fd);
		node = node->left;
	}
	fd = open(node->right->value, O_RDONLY);
	if (fd == -1)
	{
		perror(node->right->value);
		return (NULL);
	}
	close(fd);
	return (infile);
}

char	*right_redir_ins(t_node *node)
{
	int		fd;
	char	*infile;

	printf("we do go here right?\n");
	infile = node->right->right->value;
	printf("infileee is %s\n", infile);
	fd = open(node->right->left->value, O_RDONLY);
	if (fd == -1)
	{
		perror(node->right->left->value);
		return (NULL);
	}
	close(fd);
	while (node->right->type == REDIR_IN)
	{
		fd = open(node->right->left->value, O_RDONLY);
		if (fd == -1)
		{
			perror(node->right->left->value);
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

	printf("entering get_infile w %s\n", node->value);
	printf("right child is %s\n", node->right->value);
	if (node->right->type == WORD)
		infile = node->right->value;
	else
		infile = node->right->left->value;
	if (node->left->type == REDIR_IN)
		infile = left_redir_ins(node);
	else if (node->right->type == REDIR_IN)
		infile = right_redir_ins(node);
	if (infile == NULL)
		return (NULL);
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror(infile);
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
	printf("\ncurrent redir node is %s\nright child is %s\n\n", current->value, current->right->value);
	if (!current)
		return ;
	current->right->value = get_infile(current);
	if (current->right->value == NULL)
		return ;
	infile = open(current->right->value, O_RDONLY);
	original_stdin = dup(STDIN_FILENO);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close(infile);
		return ;
	}
	close(infile);
	// if (node->right->type != WORD)
	// {
	// 	execute(data, node->right);
	// }
	if (node->left->type == CMD)
	{
		// ft_putstr_fd("about to execute ", 2);
		// print_node(node->left);
		// ft_putstr_fd("\n", 2);
		execute(data, node->left);
	}
	else
	{
		// ft_putstr_fd("about to execute ", 2);
		// print_node(current->left);
		// ft_putstr_fd("\n", 2);
		execute(data, current->left);
	}
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}
