/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/02 17:50:51 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*left_redir_in_infile(t_node *node)
// {
// 	int		fd;
// 	char	*infile;

// 	infile = node->right->value;
// 	fd = 0;
// 	if (node->left->type == REDIR_IN) // goes here if a pipe is present and more redir ins to left
// 	{
// 		infile = left_redir_in_infile(node);
// 		infile = node->right->value;
// 		while (node->left->type == REDIR_IN)
// 		{
// 			fd = open(node->left->right->value, O_RDONLY);
// 			if (fd == -1)
// 			{
// 				print_error_fd("bash: %s: No such file or directory\n", node->right->value);
// 				return (NULL);
// 			}
// 			close(fd);
// 			node = node->left;
// 		}
// 		fd = open(node->right->value, O_RDONLY);
// 		if (fd == -1)
// 		{
// 			print_error_fd("bash: %s: No such file or directory\n", node->right->value);
// 			return (NULL);
// 		}
// 		close(fd);
// 	}
// }

// enters on '<'
char	*get_infile(t_node *node)
{
	int		fd;
	char	*infile;

	infile = node->right->value;
	fd = 0;
	if (node->left->type == REDIR_IN) // goes here if a pipe is present and more redir ins to left
	{
	//	infile = left_redir_in_infile(node);
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
	}
	else if (node->right->type == REDIR_IN) // goes here if no pipe is present
	{
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
	}
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
	if (infile == -1)
	{
		printf("bash: %s: No such file or directory\n", current->right->value);
		return ;
	}
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

void	handle_redir_out(t_data *data, t_node *node)
{
	int	original_stdout;
	int	outfile;

	original_stdout = dup(STDOUT_FILENO);
	while (node->right->type == REDIR_OUT)
	{
		outfile = open(node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
		{
			printf_error("Error: Open: File could not be created\n", 1);
		}
		close(outfile);
		node->right = node->right->right;
	}
	outfile = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		printf_error("Error: Open: File could not be created\n", 1);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute(data, node->left);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

void	handle_redir_append(t_data *data, t_node *node)
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
		printf_error("Error: Open: File could not be created\n", 1);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute(data, node->left);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}