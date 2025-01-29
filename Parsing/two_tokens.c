/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:15:24 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/29 08:52:35 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_two_tokens(t_data *data)
{
	char			*file_name;
	t_token_type	type;

	file_name = data->token_list->next->value;
	type = data->token_list->type;
	if (type == REDIR_OUT || type == REDIR_OUT_APPEND)
	{
		if (!check_outfile_validity(file_name, type))
			return ;
	}
	else if (data->token_list->type == REDIR_IN)
	{
		if (!check_infile_validity(file_name))
			return ;
	}
	else if (data->token_list->type == HEREDOC)
	{
		data->doc.delimiter = data->token_list->next->value;
		create_docfile(data, data->doc.delimiter);
	}
}
