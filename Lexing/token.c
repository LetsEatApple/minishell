/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:20:31 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/09 16:38:32 by lhagemos         ###   ########.fr       */
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
	t_token *new;

	new = new_token(value, type);
	add_token(head, new);
}

void	clearlist(t_token **head)
{
		t_token *ptr;

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

void	deleteone(t_token	*token)
{
	t_token *ptr;

	ptr = token->prev; //NULL?
	if (token->value != NULL)
		free(token->value);
	if (token->next == NULL)
	{
		free(token);
		if (ptr != NULL)
			ptr->next = NULL;
	}
	else
	{
		ptr->next = token->next;
		token->next->prev = ptr;
	}
	free(token);
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