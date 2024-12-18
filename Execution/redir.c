/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/18 11:51:26 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*get_current(t_node *node)
{
	if (node->type == REDIR_IN) // goes here if a pipe is present
	{
		if (open(node->right->value, O_RDONLY) == -1)
		{
			ft_printf_fd(node->right->value);
			return (NULL);
		}
		while (node->left->type == REDIR_IN)
		{
			if (open(node->left->right->value, O_RDONLY) == -1)
			{
				ft_printf_fd(node->left->right->value);
				return (NULL);
			}
			node->left = node->left->left;
		}
	}
	else if (node->right->type == REDIR_IN) // goes here if no pipe is present
	{
		while (node->right->type == REDIR_IN)
		{
			node = node->right;
			if (open(node->left->value, O_RDONLY) == -1)
			{
				printf("bash: %s: No such file or directory\n", node->left->value);
				return (NULL);
			}
		}
	}
	return (node);
}

void	handle_redir_in(t_node *node, char **envp)
{
	t_node	*current;
	char	*final_file;
	int		original_stdin;
	int		infile;

	final_file = NULL;
	current = get_current(node);
	if (current)
		final_file = current->right->value;
	if (!final_file)
		perror("malloc error");
	infile = open(final_file, O_RDONLY);
	original_stdin = dup(STDIN_FILENO);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close(infile);
		return ;
	}
	close(infile);
	execute(node->left, envp);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}

void	handle_redir_out(t_node *node, char **envp)
{
	int	original_stdout;
	int	outfile;

	original_stdout = dup(STDOUT_FILENO);
	while (node->right->type == REDIR_OUT)
	{
		outfile = open(node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
			perror("open error");
		close(outfile);
		node->right = node->right->right;
	}
	outfile = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		print_error("Error: Open: File could not be created\n", 1);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute(node->left, envp);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

void	handle_redir_append(t_node *node, char **envp)
{
	int	original_stdout;
	int	outfile;

	original_stdout = dup(STDOUT_FILENO);
	while (node->right->type == REDIR_OUT_APPEND)
	{
		outfile = open(node->right->left->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile < 0)
			perror("open error");
		close(outfile);
		node->right = node->right->right;
	}
	outfile = open(node->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile < 0)
		print_error("Error: Open: File could not be created\n", 1);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute(node->left, envp);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}