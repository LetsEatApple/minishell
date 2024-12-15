/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:33:25 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/15 14:15:28 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	connect_words(t_token **head)
{
	t_token	*ptr;
	t_token	*start;
	char	*value;

	ptr = *head;
	while (ptr)
	{
		if (ptr->word == 1)
		{
			start = ptr;
			while (ptr && ptr->word == 1)
			{
				if (ptr->next && ptr->next->word == 1)
				{
					value = start->value;
					start->value = ft_strjoin(start->value, ptr->next->value);
					if (value != NULL && value[0] != '\0')
						free(value);
				}
				ptr = ptr->next;
			}
			delete_rest(start, ptr);
		}
		else
			ptr = ptr->next;
	}
}

int	is_token_op(t_token *token)
{
	if(token->type >= 2 && token->type <= 6)
		return (true);
	return (false);
}

void	check_words(t_token **head)
{
	t_token	*ptr;

	ptr = *head;
	while (ptr && ptr->next)
	{
		if (ptr->type < 2 || ptr->type == WORD)
		{
			if (ptr->type == WORD && ptr->next->type < 2)
			{
				ptr->word = 1;
				ptr->next->word = 1;
			}
			if (ptr->type < 2 && is_token_op(ptr->next) == false
				&& ptr->next->type != 10)
			{
				ptr->word = 1;
				ptr->next->word = 1;
			}
		}
		ptr = ptr->next;
	}
}

void	remove_whitespace(t_data *data, t_token **head)
{
	t_token	*ptr;

	ptr = *head;
	while (ptr)
	{
		if (list_size(*head) == 1 && (*head)->type == WHITESPACE)
		{
			clearlist(&data->token_list);
			data->token_list = NULL;
			break ;
		}
		if (ptr->type == WHITESPACE)
		{
			delete_node(head, ptr);
			ptr = *head;
		}
		else
			ptr = ptr->next;
	}
}

void	handle_whitespaces(t_data *data, t_token **head)
{
	check_words(head);
	connect_words(head);
	remove_whitespace(data, head);
}
