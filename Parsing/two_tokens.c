/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:15:24 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/22 17:41:02 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_two_tokens(t_data *data)
{
	char	*file_name;

	file_name = NULL;
	if (data->token_list->type == REDIR_OUT)
	{
		file_name = data->token_list->next->value;
		open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//error here also possible but not likely
	}
	else if (data->token_list->type == REDIR_OUT_APPEND)
	{
		file_name = data->token_list->next->value;
		open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (data->token_list->type == REDIR_IN)
	{
		file_name = data->token_list->next->value;
		if (open(file_name, O_RDONLY) == -1)
		{
			perror(file_name);
			g_signal = 1;
		}
	}
	else if (data->token_list->type == HEREDOC)
	{
		data->doc.delimiter = data->token_list->next->value;
		create_docfile(data, data->doc.delimiter);
	}
		//handle_heredoc(data, NULL);
}
