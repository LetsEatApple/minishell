/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/15 19:22:06 by grmullin         ###   ########.fr       */
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

	infile = node->right->right->value;
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
		infile = node->right->right->value;
		node = node->right;
	}
	if (node->right->type == WORD)
		infile = node->right->value;
	else
		infile = node->right->left->value;
	return (infile);
}
// enters on '<'
char	*get_infile(t_node *node)
{
	char	*infile;
	int		fd;

	infile = node->right->value;
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
	int		original_stdout;
	int		infile;
	int		outfile;

	infile = 0;
	current = get_current(node);
	original_stdout = 0;
	outfile = 0;
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
	if (!data->pipes && current->right && (current->right->type == REDIR_OUT ||
		current->right->type == REDIR_OUT_APPEND))
	{
		original_stdout = dup(STDOUT_FILENO);
		outfile = get_outfile(data);
		if (!outfile)
			return ;
		data->outfile = outfile;
		dup2(outfile, STDOUT_FILENO); // check if -1
		close(outfile);
		execute(data, current->left);
		close(original_stdout);
	}
	if (node->left && node->left->type == CMD)
		execute(data, node->left);
	else
		execute(data, current->left);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}
