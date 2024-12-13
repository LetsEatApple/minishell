/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:51:04 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/13 13:39:00 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_arr(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (cmd[i][0] != '\0')
			printf("%s ", cmd[i]);
		else
			printf("'' ");
		i++;
	}
}

void print_token_list(t_data *data)
{
	t_token	*ptr;

	if (data->token_list == NULL)
		return;
	ptr = data->token_list;
	while (ptr != NULL) {
		if (ptr->value != NULL)
			printf("value: %s, type: %s\n", ptr->value, get_token_type(ptr->type));
		else if (ptr->cmd != NULL) {
			print_arr(ptr->cmd);
			printf(", type: %s\n", get_token_type(ptr->type));
		} else
			printf("value: NULL, type: %s\n", get_token_type(ptr->type));
		// printf("file = %d\n", ptr->file);
		ptr = ptr->next;
	}
}
