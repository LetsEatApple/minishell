/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:06:06 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/10 15:16:53 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_rest(t_token *start, t_token *end)
{
	t_token	*ptr;

	ptr = start->next;
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

	cmd = (char **)malloc((len +1) * sizeof(char *));
	ptr = start;
	i = 0;
	while (ptr != end)
	{
		if (ptr->value == NULL)
			ptr->value = ft_strdup("");
		cmd[i] = ft_strdup(ptr->value);
		ptr = ptr->next;
		i++;
	}
	cmd[i] = NULL;
	free(start->value);
	start->value = NULL;
	start->cmd = cmd;
	start->type = CMD;
	if (len != 1)
		delete_rest(start, end);
}
