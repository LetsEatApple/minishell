/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/29 11:49:05 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_infile_red_in(t_data *data, t_node *node)
{
	char	*infile;
	(void)data;

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
	if (!check_infile_validity(infile))
		return (NULL);
	return (infile);
}

void	handle_redir_in(t_data *data, t_node *node)
{
	char	*infile;
	int		original_stdin;
	
	infile = get_infile_red_in(data, node);
	if (infile == NULL )
		return ;
	data->infile = open(infile, O_RDONLY);
	original_stdin = dup(STDIN_FILENO);
	if (dup2(data->infile, STDIN_FILENO) == -1)
	{
		close(data->infile);
		ft_perror("dup25", 1);
		return ;
	}
	close(data->infile);
	ft_next_exec(data, node);
	if (dup2(original_stdin , STDIN_FILENO) == -1)
	{
		ft_perror("dup26", 1);
		return ;
	}
	close(original_stdin);
}

char	*check_infile_validity(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		g_signal = 1;
		return (NULL);
	}
	close(fd);
	return (file);
}

