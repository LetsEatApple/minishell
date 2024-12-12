/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:51:04 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/12 18:16:01 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	print_list(t_token *token_list)
{
	t_token	*ptr;

	if (token_list == NULL)
		return ;
	ptr = token_list;
	while (ptr != NULL)
	{
		if (ptr -> value != NULL)
			printf("[value: %s, type: %d] ", ptr->value, ptr->type);
		else if (ptr->cmd != NULL)
		{
			print_arr(ptr->cmd);
			printf(", type: %d] ", ptr->type);
		}
		else
			printf("[value: NULL, type: %d] ", ptr->type);
		printf("word = %d ", ptr->word);
		ptr = ptr -> next;
	}
	printf("\n");
}
