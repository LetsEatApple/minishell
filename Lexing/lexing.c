/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:47:04 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/01 15:57:50 by lhagemos         ###   ########.fr       */
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
		create_list(head, value, type);
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
	int		j;
	int		len;
	char	*value;
	char	**words;

	len = get_value_len(input, *i, WORD);
	words = split_string(input, *i, len);
	if (words[0] == 0)
	{
		free_splits(words);
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
	free_splits(words);
	*i += len;
	return ;
}

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

int	lexing(char *input)
{
	int		i;
	t_token	*head;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			process_quote(&head, input, &i);
		if (check_char(input[i]) == WORD)
			process_word(&head, input, &i);
		if (check_char(input[i]) == PIPE)
			process_pipe(&head, input, &i);
		if (check_char(input[i]) == 3 || check_char(input[i]) == 4)
			process_redir(&head, input, &i);
	}
	check_syntax(&head);
	print_list(&head);
	return (true);
}

	//add to process_word	
/* value = create_string(input, *i, len);
	*i = *i + len;
	if (value == NULL)
		type = WHITESPACE;
	create_list(head, value, type);
	return ;
*/

/* char *connect_words(char **words)
{
	int		i;
	char	*string;
	char	*temp;
	
	i = 0;
	string = "";
	temp = "";
	while(words[i] != 0)
	{
		if (words[i+1] == 0)
		{
			temp = string;
			string = ft_strjoin(string, words[i]);
			if (temp[0] != '\0')
				free(temp);
		}	
		else
		{
			temp = ft_strjoin(string, words[i]);
			if (string[0] != '\0')
				free(string);
			string = ft_strjoin(temp, " ");
			free(temp);
		}
		i++;
	}
	free_splits(words);
	return (string);
} */