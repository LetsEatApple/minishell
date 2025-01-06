/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:50:56 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/06 14:44:50 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_size(t_token *head)
{
	int		size;
	t_token	*ptr;

	size = 0;
	ptr = head;
	while (ptr)
	{
		size++;
		ptr = ptr->next;
	}
	return (size);
}

static void	free_node(t_token *ptr)
{
	if (ptr->value != NULL) //&& todelete->value[0] != '\0' ?
		free(ptr->value);
	free(ptr);
}

void	delete_node(t_token **head, t_token *todelete)
{
	t_token	*ptr;

	if (*head == todelete)
	{
		*head = (*head)->next;
		free_node((*head)->prev);
		(*head)->prev = NULL;
	}
	else if (todelete->next == NULL)
	{
		ptr = todelete->prev;
		free_node(todelete);
		ptr->next = NULL;
	}
	else
	{
		ptr = todelete->prev;
		ptr->next = todelete->next;
		todelete->next->prev = ptr;
		free_node(todelete);
		todelete = NULL;
	}
}

void	delete_nullword(t_data *data, t_token **head)
{
	t_token	*ptr;

	ptr = *head;
	while (ptr)
	{
		if (list_size(*head) == 1 && (*head)->value == NULL
			&& (*head)->type == WORD)
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

void	connect_val(t_token *ptr, t_token *start)
{
	char	*value;

	value = start->value;
	start->value = ft_strjoin(start->value, ptr->next->value);
	if (value != NULL && value[0] != '\0')
		free(value);
}

/* if (ptr->next && ptr->next->word == 1)
{
	value = start->value;
	start->value = ft_strjoin(start->value, ptr->next->value);
	if (value != NULL && value[0] != '\0')
		free(value);
} */