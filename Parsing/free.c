/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:30:23 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/09 10:17:56 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_table(t_data *data)
{
	free_ast(data->root);
	data->pipes = 0;
	data->redirs = 0;
	data->root = NULL;
}

void	free_ast(t_node *head)
{
	if (head->value == NULL)
		return ;
	if (head->left)
		free_ast(head->left);
	if (head->right)
		free_ast(head->right);
	if (head->value != NULL)
		free(head->value);
	free(head);
}
