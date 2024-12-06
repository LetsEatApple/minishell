/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:51:04 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/06 15:23:34 by grmullin         ###   ########.fr       */
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
			printf("value: %s, type: %d noded: '%d'\n", ptr->value, ptr->type, ptr->node);
		else
			printf("value: NULL, type: %d\n", ptr->type);
		ptr = ptr -> next;
		}
	//clearlist(&data->token_list);
}
