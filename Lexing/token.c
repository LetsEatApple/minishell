/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:20:31 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/06 17:11:09 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token(t_token **head, t_token *new)
{
		t_token *ptr;

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

t_token *new_token(char *value, t_token_type type)
{
		t_token *new;

		new = malloc(sizeof(t_token));
		if (!new)
			return (0);
		new -> prev = NULL;
		new -> value = value;
		new->node = 0;
		new->root = 0;
		new -> type = type;
		new -> next = NULL;
		return (new);
}

void	create_list(t_token **head, char *value, t_token_type type)
{
	t_token *new;

	new = new_token(value, type);
	add_token(head, new);
}

void	clearlist(t_token **head)
{
	t_token *ptr;
	
	if (*head == NULL)
		return ;
	ptr = *head;
	while (ptr != NULL)
	{
		if (ptr->next == NULL)
		{
			free(ptr->value);
			free(ptr);
			break ;
		}
		free(ptr->value);
		ptr = ptr->next;
		free(ptr->prev);
	}
}


/* void	create_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new;
	t_token *ptr;

	ptr = *head;
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = value;
	new->type = type;
	if (*head == NULL)
	{
		*head = new;
		new ->prev = NULL;
		new -> next = NULL;
	}
	else
	{
		while (ptr && ptr -> next != NULL)
			ptr = ptr -> next;
		ptr -> next = new;
		new -> prev = ptr;
	}
} */