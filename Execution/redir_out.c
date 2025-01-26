/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:08:47 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/26 20:57:46 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redir_out(t_data *data, t_node *node)
{
	char *outfile;
	int	fd;

	outfile = get_outfile_redir_out(node);
	if (!outfile)
		return ;
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (data->pipes == 0 && node->right->type == REDIR_IN && check_for_infile(data, node))
		return ;
	if (node->left)
		execute(data, node->left);
	dup2(data->std_out_fd, STDOUT_FILENO);
	close(data->std_out_fd);
}

char	*get_outfile_red_app(t_node *node)
{
	char	*file;

	while (node->right && node->right->type == REDIR_OUT_APPEND)
	{
		file = node->right->left->value;
		if (!check_outfile_validity(file, REDIR_OUT_APPEND))
			return (NULL);
		node = node->right;
	}
	file = node->right->value;
	if (node->right->type == REDIR_OUT)
		file = get_outfile_redir_out(node);
	if (!check_outfile_validity(file, REDIR_OUT_APPEND))
		return (NULL);
	return (file);
}

void	handle_redir_append(t_data *data, t_node *node)
{
	char	*outfile;
	int		fd;

	outfile = get_outfile_redir_out(node); // get_outfile_red_app(node);
	if (!outfile)
	{
		g_signal = 1;
		return ;
	}
	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	data->outfile = fd;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (node->left)
		execute(data, node->left);
	dup2(data->std_out_fd, STDOUT_FILENO);
	close(data->std_out_fd);
}
