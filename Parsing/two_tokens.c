/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:15:24 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/16 13:10:17 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_two_tokens(t_data *data)
{
	char	*file_name;

	file_name = NULL;
	if (data->token_list->type == REDIR_OUT
		&& data->token_list->next->type == WORD)
	{
		file_name = data->token_list->next->value;
		open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (data->token_list->type == REDIR_IN
		&& data->token_list->next->type == WORD)
	{
		file_name = data->token_list->next->value;
		if (open(file_name, O_RDONLY) == -1)
			printf("bash: %s: No such file or directory\n", file_name);
	}
}
