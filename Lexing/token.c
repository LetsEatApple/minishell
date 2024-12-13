/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:20:31 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/13 13:31:54 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token(t_token **head, t_token *new)
{
	t_token	*ptr;

	if (!head || !new)
		return ;
	ptr = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (ptr -> next != NULL)
			ptr = ptr -> next;
		ptr -> next = new;
		new -> prev = ptr;
	}
}

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new -> value = value;
	new -> cmd = NULL;
	new -> type = type;
	new -> file = 0;
	new->node = 0;
	new->root = 0;
	new -> next = NULL;
	new -> prev = NULL;
	return (new);
}

void	create_list(t_token **head, char *value, t_token_type type)
{
	t_token	*new;

	new = new_token(value, type);
	add_token(head, new);
}

void	clearlist(t_token **head)
{
	t_token	*ptr;
	t_token	*next;

	if (!head || !*head)
		return;
	ptr = *head;
	while (ptr != NULL)
	{
		next = ptr->next;
		if (ptr->value)
		{
			free(ptr->value);
			ptr->value = NULL;
		}
		if (ptr->cmd && !ptr->node)
		{
			free_split(ptr->cmd);
			ptr->cmd = NULL;
		}
		free(ptr);
		ptr = next;
	}
	*head = NULL;
}
