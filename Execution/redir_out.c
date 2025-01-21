/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:08:47 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/21 15:25:30 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_outfile_red_out(t_node *node)
{
	int		fd;

	fd = 0;
	while (node->right->type == REDIR_OUT && node->right->type != WORD)
	{
		fd = open(node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(node->right->left->value);
			g_signal = 1;
			return (0);
		}
		close(fd);
		node = node->right;
	}
	fd = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(node->right->value);
		g_signal = 1;
		return (0);
	}
	return (fd);
}

void	handle_redir_out(t_data *data, t_node *node)
{
	int	original_stdout;
	int	outfile;

	original_stdout = dup(STDOUT_FILENO);
	outfile = get_outfile_red_out(node);
	if (!outfile)
		return ;
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	if (node->left)
		execute(data, node->left);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

int	get_outfile_red_app(t_node *node)
{
	char	*file;
	int		fd;

	while (node->right->type == REDIR_OUT_APPEND)
	{
		file = node->right->left->value;
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(file);
			g_signal = 1;
			return (0);
		}
		close(fd);
		node = node->right;
	}
	fd = open(node->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(node->right->value);
		g_signal = 1;
		return (0);
	}
	return (fd);
}

void	handle_redir_append(t_data *data, t_node *node)
{
	int	original_stdout;
	int	outfile;

	original_stdout = dup(STDOUT_FILENO);
	outfile = get_outfile_red_app(node);
	if (!outfile)
	{
		g_signal = 1;
		return ;
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	if (node->left)
		execute(data, node->left);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}
