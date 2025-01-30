/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/30 17:51:51 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_infile_red_in(t_node *node)
{
	char	*infile;

	if (node->prev == NULL && node->right->type == WORD)
		infile = node->right->value;
	else if (node->prev == NULL)
		infile = node->right->left->value;
	else if (node->right && node->right->type == WORD)
		infile = node->right->value;
	else if (node->left && node->left->type == WORD)
		infile = node->left->value;
	if (infile == NULL)
		return (NULL);
	if (!check_file_validity(infile, REDIR_IN))
		return (NULL);
	return (infile);
}

void	handle_redir_in(t_data *data, t_node *node)
{
	char	*infile;
	int		original_stdin;

	infile = get_infile_red_in(node);
	if (infile == NULL )
		return ;
	data->infile = open(infile, O_RDONLY);
	original_stdin = dup(STDIN_FILENO);
	if (dup2(data->infile, STDIN_FILENO) == -1)
	{
		close(data->infile);
		ft_perror("dup2", 1);
		return ;
	}
	close(data->infile);
	if (check_next_exec(data, node) == true)
	{
		//data->std_in_fd = original_stdin;
		ft_next_exec(data, node);
		if (dup2(original_stdin, STDIN_FILENO) == -1)
		{
			ft_perror("dup23", 1);
			return;
		}
		close(original_stdin);
	}
	else
	{
		if (dup2(original_stdin, STDIN_FILENO) == -1)
		{
			ft_perror("dup23", 1);
			return;
		}
		close(original_stdin);
		ft_next_exec(data, node);
	}
	// ft_next_exec(data, node);
	// if (dup2(original_stdin, STDIN_FILENO) == -1)
	// {
	// 	ft_perror("dup2", 1);
	// 	return ;
	// }
	// close(original_stdin);
}
