/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:20:31 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/10 13:56:39 by lhagemos         ###   ########.fr       */
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

void	delete_node(t_token **head, t_token *todelete)
{
	t_token	*ptr;

	if (*head == todelete)
	{
		*head = (*head)->next;
		free((*head)->prev);
		(*head)->prev = NULL;
	}
	else if (todelete->next == NULL)
	{
		ptr = todelete->prev;
		free(todelete);
		ptr->next = NULL;
	}
	else
	{
		ptr = todelete->prev;
		ptr->next = todelete->next;
		todelete->next->prev = ptr;
		free(todelete);
		todelete = NULL;
	}
}

void	delete_nullword(t_data *data, t_token **head)
{
	t_token	*ptr;

	ptr = *head;
	while (ptr)
	{
		if (list_size(*head) == 1 && (*head)->value == NULL && (*head)->type == WORD)
		{
			clearlist(&data->token_list);
			data->token_list = NULL;
			break ;
		}
		if (ptr->value == NULL && ptr->type == WORD)
		{
			delete_node(head, ptr);
			ptr = *head;
		}
		else
			ptr = ptr->next;
	}
}

/* if (token->next != NULL)
		token->next->prev = token->prev;
	if (token->prev != NULL)
		token->prev->next = token->next;
	if (token->value != NULL)
		free(token->value);
	ft_memset(token, 0, sizeof(t_token));
	free(token); */
	
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