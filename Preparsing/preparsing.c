/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:00:28 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/12 18:28:35 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_ops(t_data *data)
{
	t_token	*ptr;

	ptr = data->token_list;
	while (ptr != NULL)
	{
		if (ptr->type > 2 && ptr->type < 7)
			data->redirs++;
		if (ptr->type == PIPE)
			data->pipes++;
		ptr = ptr->next;
	}
}

void	get_files(t_token *head)
{
	t_token	*ptr;

	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->type > 2 && ptr->type < 7)
		{
			ptr = ptr->next;
			ptr->file = 1;
		}
		else
			ptr = ptr->next;
	}
}

void	search_cmd(t_token **head)
{
	t_token	*ptr;
	t_token	*temp;
	int		len;

	ptr = *head;
	while (ptr != NULL)
	{
		len = 0;
		if ((ptr->type == WORD || ptr->type < 2) && ptr->file == false)
		{
			temp = ptr;
			while (ptr && (ptr->type == WORD || ptr->type < 2))
			{
				len++;
				ptr = ptr->next;
			}
			store_cmd(temp, ptr, len);
		}
		else
			ptr = ptr->next;
	}
}

void	replace_envvar(t_data *data)
{
	t_token	*ptr;

	ptr = data->token_list;
	while (ptr)
	{
		if (ptr->value != NULL && check_dollar(ptr->value) == true
			&& ptr->type != SINGLE_QUOTE)
			switch_value(ptr, data->env);
		ptr = ptr->next;
	}
	delete_nullword(data, &data->token_list);
}

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
			if (ptr->type < 2 && is_token_op(ptr->next) == false && ptr->next->type != 10)
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

void	preparsing(t_data *data)
{
	count_ops(data);
	replace_envvar(data);
	check_words(&data->token_list);
	connect_words(&data->token_list);
	remove_whitespace(data, &data->token_list);
	get_files(data->token_list);
	search_cmd(&data->token_list);
	modify_cmd(data);
}
