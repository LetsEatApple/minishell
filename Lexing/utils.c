/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:51:04 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/02 19:07:03 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	free_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		free(splits[i]);
		i++;
	}
	free(splits);
} */

void	print_list(t_data *data)
{
	t_token *ptr;
	
	if (data->token_list == NULL)
		return ;
	ptr = data->token_list;
	while (ptr != NULL)
	{
		if (ptr -> value != NULL)
			printf("value: %s, type: %d\n", ptr->value, ptr->type);
		else
			printf("value: NULL, type: %d\n", ptr->type);
		ptr = ptr -> next;
		}
	//clearlist(&data->token_list);
}
