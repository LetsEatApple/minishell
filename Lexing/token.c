/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:20:31 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/10 14:50:51 by lhagemos         ###   ########.fr       */
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

	if (*head == NULL || !*head)
		return ;
	ptr = *head;
	while (ptr != NULL)
	{
		if (ptr->next == NULL)
		{
			if (ptr->value != NULL)
				free(ptr->value);
			if (ptr->cmd != NULL)
				free_split(ptr->cmd);
			free(ptr);
			break ;
		}
		if (ptr->value != NULL)
			free(ptr->value);
		if (ptr->cmd != NULL)
			free_split(ptr->cmd);
		ptr = ptr->next;
		free(ptr->prev);
	}
}
