/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:47:04 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/23 13:38:59 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_quote(t_token **head, char *input, int *i)
{
	int				len;
	char			*value;
	t_token_type	type;

	value = NULL;
	if (input[*i] == 39)
		type = SINGLE_QUOTE;
	else
		type = DOUBLE_QUOTE;
	len = get_value_len(input, *i, type);
	if (input[*i + len] == '\0')
	{
		syntax_error(head, input[*i]);
		*i = ft_strlen(input);
		return ;
	}
	if (len == 1)
		create_list(head, ft_strdup(""), type);
	else
	{
		value = copy_part(input, *i +1, len -1);
		create_list(head, value, type);
	}
	*i += len +1;
	return ;
}

void	process_word(t_token **head, char *input, int *i)
{
	int		len;
	char	*value;

	if (input[*i] == '\0')
		return ;
	if (check_char(input[*i]) == WHITESPACE)
	{
		len = get_value_len(input, *i, WHITESPACE);
		create_list(head, NULL, WHITESPACE);
		*i += len;
	}
	else
	{
		len = get_value_len(input, *i, WORD);
		value = copy_part(input, *i, len);
		create_list(head, value, WORD);
		*i += len;
	}
	return ;
}

/* void	process_word(t_token **head, char *input, int *i)
{
	int		j;
	int		len;
	char	*value;
	char	**words;

	len = get_value_len(input, *i, WORD);
	words = split_string(input, *i, len);
	if (words[0] == 0)
	{
		free_split(words);
		*i += len;
		return ;
	}
	j = 0;
	while (words[j] != 0)
	{
		value = ft_strdup(words[j]);
		create_list(head, value, WORD);
		j++;
	}
	free_split(words);
	*i += len;
	return ;
} */

void	process_pipe(t_token **head, char *input, int *i)
{
	int		len;
	char	*value;

	len = get_value_len(input, *i, PIPE);
	if (len != 1)
	{
		syntax_error(head, input[*i]);
		*i = ft_strlen(input);
		return ;
	}
	value = copy_part(input, *i, len);
	create_list(head, value, PIPE);
	*i += len;
}

void	process_redir(t_token **head, char *input, int *i)
{
	int				len;
	char			*value;
	t_token_type	type;

	type = check_char(input[*i]);
	len = get_value_len(input, *i, type);
	if (len > 2)
	{
		syntax_error(head, input[*i]);
		*i = ft_strlen(input);
		return ;
	}
	value = copy_part(input, *i, len);
	if (len == 2)
		type = type +2;
	create_list(head, value, type);
	*i += len;
}

/* void	process_whitespace(t_token **head, char *input, int *i)
{
	int		len;

	len = get_value_len(input, *i, WHITESPACE);
	create_list(head, NULL, WHITESPACE);
	*i += len;
	return ;
} */

int	lexing(t_data *data)
{
	int		i;
	t_token	*head;
	char	*input;

	head = NULL;
	input = data->input;
	i = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			process_quote(&head, input, &i);
		if (check_char(input[i]) == WHITESPACE || check_char(input[i]) == WORD)
			process_word(&head, input, &i);
		if (check_char(input[i]) == PIPE)
			process_pipe(&head, input, &i);
		if (check_char(input[i]) == 3 || check_char(input[i]) == 4)
			process_redir(&head, input, &i);
	}
	check_syntax(&head);
	data->token_list = head;
	return (true);
}
