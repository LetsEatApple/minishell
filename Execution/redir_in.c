/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/24 17:25:20 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*left_redir_ins(t_node *node, t_token_type type)
{
	int		fd;
	char	*infile;

	infile = node->right->value;
	while (node->left->type == type)
	{
		fd = open(node->left->right->value, O_RDONLY);
		if (fd < 0)
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

char	*right_redir_ins(t_node *node, t_token_type type)
{
	int		fd;
	char	*infile;

	fd = open(node->right->left->value, O_RDONLY);
	if (fd == -1)
	{
		perror(node->right->left->value);
		g_signal = 1;
		return (NULL);
	}
	close(fd);
	while (node->right->type == type)
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
	infile = node->right->value;
	if (node->right->type != WORD)
		infile = node->right->left->value;
	return (infile);
}

char	*get_infile_red_in(t_node *node)
{
	char	*infile;
	int		fd;

	if (node->right->type == WORD)
		infile = node->right->value;
	else
		infile = node->right->left->value;
	if (node->left && node->left->type == REDIR_IN)
		infile = left_redir_ins(node, REDIR_IN);
	else if (node->right && node->right->type == REDIR_IN)
		infile = right_redir_ins(node, REDIR_IN);
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

t_node	*get_current(t_node *node)
{
	if (node->left)
	{
		while (node->left->type == REDIR_IN)
			node = node->left;
	}
	if (node->right)
	{
		while (node->right->type == REDIR_IN)
			node = node->right;
	}
	return (node);
}

void	handle_redir_in(t_data *data, t_node *node)
{
	t_node	*current;
	int		original_stdin;
	int		infile;
	char	*outfile;
	int		fd;

	current = get_current(node);
	outfile = NULL;
	fd = 0;
	if (!current)
		return ;
	current->right->value = get_infile_red_in(node);
	if (current->right->value == NULL)
	{
		dup2(data->std_out_fd, STDOUT_FILENO);
	{
		dup2(data->std_out_fd, STDOUT_FILENO);
		return ;
	}
	}
	infile = open(current->right->value, O_RDONLY);
	data->infile = infile;
	original_stdin = dup(STDIN_FILENO);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close(infile);
		return ;
	}
	close(infile);
	if (!data->pipes && current->right && current->right->type != WORD)
	{
		if (current->right->type == REDIR_OUT)
			outfile = get_outfile_red_out(current->right);
		else if (current->right->type == REDIR_OUT_APPEND)
			outfile = get_outfile_red_app(current->right);
		if (!outfile)
		{
			dup2(original_stdin , STDIN_FILENO);
			return ;
		}
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return ;
		}
		close(fd);
		if (current->left->type == CMD)
			execute(data, current->left);
		else
			execute(data, node->left);
		dup2(data->std_out_fd , STDOUT_FILENO);
	}
	else
	{
		if (current->left && current->left->type == CMD)
			execute(data, current->left);
		else if(node->left && node->left->type == CMD)
			execute(data, node->left);
	}
	dup2(original_stdin , STDIN_FILENO);
	close(original_stdin);
}
