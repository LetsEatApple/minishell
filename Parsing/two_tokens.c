/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:15:24 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/29 12:16:29 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_two_tokens(t_data *data)
{
	char			*file_name;
	t_token_type	type;

	file_name = data->token_list->next->value;
	type = data->token_list->type;
	if (type > 2 && type < 6)
	{
		if (!check_file_validity(file_name, type))
			return ;
	}
	else if (data->token_list->type == HEREDOC)
	{
		data->doc.delimiter = data->token_list->next->value;
		create_docfile(data, data->doc.delimiter);
	}
}
