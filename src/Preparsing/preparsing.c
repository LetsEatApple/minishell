/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:00:28 by lhagemos          #+#    #+#             */
/*   Updated: 2025/02/02 16:26:15 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (ptr->type == REDIR_IN)
			data->red_in++;
		if (ptr->type == HEREDOC)
			data->heredoc++;
		ptr = ptr->next;
	}
	data->ops = data->redirs + data->pipes;
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
			while (ptr && ptr->type != PIPE)
			{
				if ((ptr->type == WORD || ptr->type < 2) && ptr->file == false)
				{
					len++;
					ptr->arg = 1;
				}
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

void	preparsing(t_data *data)
{
	replace_envvar(data);
	handle_whitespaces(data, &data->token_list);
	get_files(data->token_list);
	search_cmd(&data->token_list);
	delete_arg(&data->token_list);
	modify_cmd(data);
	count_ops(data);
	init_heredoc(data);
}
