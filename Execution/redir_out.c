/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:08:47 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/22 17:18:51 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_outfile_red_out(t_node *node)
{
	char	*outfile;
	int		fd;

	if (node->left && node->left->type == WORD)
	{
		fd = open(node->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(node->left->value);
			g_signal = 1;
			return (0);
		}
		close(fd);
	}
	while (node->right->type == REDIR_OUT)
	{
		if (node->right->left->type == WORD)
		{
			fd = open(node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(node->right->left->value);
				g_signal = 1;
				return (0);
			}
			close(fd);
		}
		node = node->right;
	}
	while (node->left && (node->left->type == 3 || node->left->type == 5))
	{
		if (node->left->type == 3)
		{
			fd = open(node->left->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(node->left->right->value);
				g_signal = 1;
				return (0);
			}
			close(fd);
		}
		else if (node->left->type == 5)
		{
			fd = open(node->left->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(node->left->right->value);
				g_signal = 1;
				return (0);
			}
			close(fd);
		}
		node = node->left;
	}
	outfile = node->right->value;
	if (node->right->type != WORD)
		outfile = node->right->left->value;
	if (node->right->type == REDIR_OUT_APPEND)
		outfile = get_outfile_red_app(node);
	if (!outfile)
		return (NULL);
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(outfile);
		g_signal = 1;
		return (0);
	}
	return (outfile);
}

void	handle_redir_out(t_data *data, t_node *node)
{
	char	*outfile;
	int		fd;
	int		original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	outfile = get_outfile_red_out(node);
	if (!outfile)
		return ;
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (data->pipes == 0 && node->right->type == REDIR_IN && check_for_infile(data, node))
		return ;
	if (node->left)
		execute(data, node->left);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

char	*get_outfile_red_app(t_node *node)
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
	file = node->right->value;
	if (node->right->type == REDIR_OUT)
		file = get_outfile_red_out(node);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(file);
		g_signal = 1;
		return (0);
	}
	close(fd);
	return (file);
}

void	handle_redir_append(t_data *data, t_node *node)
{
	char	*outfile;
	int		fd;

	outfile = get_outfile_red_app(node);
	if (!outfile)
	{
		g_signal = 1;
		return ;
	}
	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (node->left)
		execute(data, node->left);
	dup2(data->std_out_fd, STDOUT_FILENO);
	close(data->std_out_fd);
}
