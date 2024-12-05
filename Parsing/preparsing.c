/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:00:28 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/05 15:15:19 by lhagemos         ###   ########.fr       */
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
	t_token *ptr;

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

void	delete_rest(t_token *start, t_token *end)
{
	t_token *ptr;

	ptr = start;
	while (ptr != end)
	{
		if (ptr->value != NULL)
			free(ptr->value);
		if (ptr->next == NULL)
		{
			free(ptr);
			break ;
		}
		ptr = ptr->next;
		free(ptr->prev);
	}
	start->next = end;
	if (end != NULL)
		end->prev = start;
}

void	store_cmd(t_token *start, t_token *end, int len)
{
	t_token	*ptr;
	char	**cmd;
	int		i;

	cmd = (char **)malloc(len * sizeof(char *));
	ptr = start;
	i = 0;
	while (ptr != end)
	{
		cmd[i] = ft_strdup(ptr->value);
		ptr = ptr->next;
		i++;
	}
	cmd[i] = NULL;
	free(start->value);
	start->value = NULL;
	start->cmd = cmd;
	start->type = CMD;
	delete_rest(start, end);
}

void	search_cmd(t_token **head)
{
	t_token *ptr;
	//t_token	*temp;
	int		len;

	ptr = *head;
	while (ptr != NULL)
	{
		len = 0;
		if ((ptr->type == WORD || ptr->type < 2) && ptr->file == false)
		{
			//temp = ptr;
			while (ptr && (ptr->type == WORD || ptr->type < 2))
			{
				len++;
				ptr = ptr->next;
			}
			if (ptr != NULL)
				printf("ptr= %d\n", ptr->type);
			else
				printf("ptr= NULL\n");
			printf("len: %d\n", len);
			//store_cmd(temp, ptr, len);
		}
		else
			ptr = ptr->next;
	}
}

void	preparsing(t_data *data)
{
	
	count_ops(data);
	get_files(data->token_list);
	search_cmd(&data->token_list);
}