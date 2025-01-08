/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:15:24 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/08 18:17:31 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_two_tokens(t_data *data)
{
	char	*file_name;

	file_name = NULL;
	if ((data->token_list->type == REDIR_OUT
			|| data->token_list->type == REDIR_OUT_APPEND)
		&& data->token_list->next->type == WORD)
	{
		file_name = data->token_list->next->value;
		open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (data->token_list->type == REDIR_IN
		&& data->token_list->next->type == WORD) // is ths line always true?
	{
		file_name = data->token_list->next->value;
		if (open(file_name, O_RDONLY) == -1)
			print_error_fd("%s: No such file or directory\n", file_name, 1);
	}
}
