/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:21:57 by grmullin          #+#    #+#             */
/*   Updated: 2025/02/02 16:49:01 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_data(t_data *data)
{
	restore_std(data, 2);
	if (data->input != NULL)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->token_list != NULL)
	{
		clearlist(&data->token_list);
		data->token_list = NULL;
	}
	if (data->doc.file)
	{
		if (access(data->doc.file, F_OK) == 0)
			unlink(data->doc.file);
		free(data->doc.file);
		data->doc.file = NULL;
	}
	clear_table(data);
}

void	free_split(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (s[i])
		{
			free(s[i]);
			s[i] = NULL;
		}
		i++;
	}
	if (s)
		free(s);
}

void	clear_table(t_data *data)
{
	if (data->root != NULL)
	{
		free_ast(data->root);
		data->root = NULL;
	}
	if (data->token_list != NULL)
	{
		clearlist(&data->token_list);
		data->token_list = NULL;
	}
	data->pipes = 0;
	data->redirs = 0;
	data->red_in = 0;
	data->heredoc = 0;
	if (data->outfile >= 0)
	{
		close(data->outfile);
		data->outfile = -1;
	}
	if (data->infile >= 0)
	{
		close(data->infile);
		data->infile = -1;
	}
}

void	free_ast(t_node *head)
{
	if (!head)
		return ;
	if (head->left != NULL)
	{
		free_ast(head->left);
		head->left = NULL;
	}
	if (head->right != NULL)
	{
		free_ast(head->right);
		head->right = NULL;
	}
	if (head->cmd)
	{
		free_split(head->cmd);
		head->cmd = NULL;
	}
	if (head)
		free(head);
	head = NULL;
}

void	clear_elist(t_data *data, t_env **head)
{
	t_env	*ptr;
	t_env	*next;

	if (!head || !*head)
		return ;
	ptr = *head;
	while (ptr != NULL)
	{
		next = ptr->next;
		if (ptr->value != NULL)
		{
			free(ptr->value);
			ptr->value = NULL;
		}
		if (ptr->var != NULL)
		{
			free(ptr->var);
			ptr->var = NULL;
		}
		free(ptr);
		ptr = next;
	}
	*head = NULL;
	data->e_list = NULL;
}
