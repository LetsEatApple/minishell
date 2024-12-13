/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:21:57 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/13 12:51:01 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data(t_data *data)
{
	if (data->input != NULL)
	{
		free(data->input);
		data->input = NULL;
	}
	data->pipes = 0;
	data->redirs = 0;
	if (data->token_list != NULL)
	{
		clearlist(&data->token_list);
		data->token_list = NULL;
	}
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
	data->pipes = 0;
	data->redirs = 0;
}

void	free_ast(t_node *head)
{
	if (!head)
		return ;
	if (head->left != NULL)
		free_ast(head->left);
	if (head->right != NULL)
		free_ast(head->right);
	if (head->cmd)
	{
		free_split(head->cmd);
		head->cmd = NULL;
	}
	if (head->value)
	{
		free(head->value);
		head->value = NULL;
	}
	free(head);
}
