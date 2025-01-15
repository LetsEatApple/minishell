/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/15 14:25:38 by grmullin         ###   ########.fr       */
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
			g_signal = 1;
			return (NULL);
		}
		close(fd);
		node = node->left;
	}
	fd = open(node->right->value, O_RDONLY);
	if (fd == -1)
	{
		perror(node->right->value);
		g_signal = 1;
		return (NULL);
	}
	close(fd);
	return (infile);
}

char	*right_redir_ins(t_node *node)
{
	int		fd;
	char	*infile;

	infile = node->right->left->value;
	fd = open(node->right->left->value, O_RDONLY);
	if (fd == -1)
	{
		perror(node->right->left->value);
		g_signal = 1;
		return (NULL);
	}
	close(fd);
	while (node->right->type == REDIR_IN)
	{
		fd = open(node->right->left->value, O_RDONLY);
		if (fd == -1)
		{
			perror(node->right->left->value);
			g_signal = 1;
			return (NULL);
		}
		close(fd);
		infile = node->right->left->value;
		node = node->right;
	}
	infile = node->right->value;
	return (infile);
}
// enters on first '<' in tree
char	*get_infile(t_node *node)
{
	t_node	*temp;
	char	*infile;
	int		fd;

	temp = node;
	if (temp->right->type == WORD)
		infile = temp->right->value;
	else
		infile = temp->right->left->value;
	if (temp->left && temp->left->type == REDIR_IN)
		infile = left_redir_ins(temp);
	else if (temp->right && temp->right->type == REDIR_IN)
		infile = right_redir_ins(temp);
	if (infile == NULL)
		return (NULL);
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror(infile);
		g_signal = 1;
		return (NULL);
	}
	close(fd);
	return (infile);
}

t_node	*get_current(t_node *temp)
{
	if (temp->left)
	{
			while (temp->left->type == REDIR_IN)
		temp = temp->left;
	}
	if (temp->right)
	{
		while (temp->right->type == REDIR_IN)
		temp = temp->right;
	}
	return (temp);
}

int	get_outfile(t_data *data)
{
	t_node	*temp;
	char	*outfile;
	int		outfile_fd;

	temp = data->root;
	while (temp->right->type != WORD)
		temp = temp->right;
	outfile = temp->right->value;
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror(outfile);
		return (0);
	}
	return (outfile_fd);
}

void	handle_redir_in(t_data *data, t_node *node)
{
	t_node	*current;
	int		original_stdin;
	int		infile;
	int		original_stdout;
	int 	outfile;

	infile = 0;
	outfile = 0;
	original_stdout = 0;
	current = get_current(node);
	if (!current)
		return ;
	current->right->value = get_infile(node);
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
	if (node->left && node->left->type == EMPTY)
	{
		execute(data, node->right);
		return ;
	}
	if (!data->pipes && node->left && (node->left->type == REDIR_OUT ||
		node->left->type == REDIR_OUT_APPEND))
	{
		original_stdout = dup(STDOUT_FILENO);
		outfile = get_outfile(data);
		if (!outfile)
			return ;
		dup2(outfile, STDOUT_FILENO); // check if -1
		close(outfile);
	}
	if (node->left && node->left->type == CMD)
		execute(data, node->left);
	else
		execute(data, current->left);
//	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}
