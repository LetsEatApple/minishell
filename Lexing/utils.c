/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:51:04 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/01 15:12:18 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		free(splits[i]);
		i++;
	}
	free(splits);
}

void	print_list(t_token **head)
{
	t_token *ptr;
	
	if (*head == NULL)
		return ;
	ptr = *head;
	while (ptr != NULL)
	{
		if (ptr -> value != NULL)
			printf("value: %s, type: %d\n", ptr->value, ptr->type);
		else
			printf("value: NULL, type: %d\n", ptr->type);
		ptr = ptr -> next;
		}
	clearlist(head);
}
