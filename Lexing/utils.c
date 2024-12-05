/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:51:04 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/05 13:51:28 by lhagemos         ###   ########.fr       */
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

void	print_arr(char **cmd)
{
	int i;
	
	i = 0;
	printf("cmd: ");
	while (cmd[i] != NULL)
	{
		printf("%s, ", cmd[i]);
		i++;
	}
}

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
		else if (ptr->cmd != NULL)
		{
			print_arr(ptr->cmd);
			printf(", type: %d\n", ptr->type);
		}
		else
			printf("value: NULL, type: %d\n", ptr->type);
		printf("file = %d\n", ptr->file);
		ptr = ptr -> next;
		}
	//clearlist(&data->token_list);
}
