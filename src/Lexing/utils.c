/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:51:04 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/31 21:01:19 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_arr(char **cmd)
{
	int	i;

	i = 0;
	printf("[cmd: ");
	while (cmd[i] != NULL)
	{
		if (cmd[i][0] != '\0')
			printf("%s ", cmd[i]);
		else
			printf("'' ");
		i++;
	}
}

/* void	print_token_list(t_token *token_list)
{
	t_token	*ptr;

	if (token_list == NULL)
		return ;
	ptr = token_list;
	while (ptr != NULL)
	{
		if (ptr->value != NULL)
		{
			printf("[value: '%s', ", ptr->value);
			printf("type: %s] ", get_token_type(ptr->type));
		}
		else if (ptr->value && ptr->value[0] == '\0')
		{
			printf("[value: 'empty', ");
			printf("type: %s] ", get_token_type(ptr->type));
		}
		else if (ptr->cmd != NULL)
		{
			print_arr(ptr->cmd);
			printf(" , type: %s] ", get_token_type(ptr->type));
		}
		else
			printf("[value: NULL, type: %s] ", get_token_type(ptr->type));
		printf(" int word: %d", ptr->word);
		printf("\n");
		ptr = ptr -> next;
	}
	printf("\n");
} */
