/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:10:19 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/12 19:01:54 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_wspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\f' || c == '\v' || c == '\r')
		return (true);
	return (false);
}

t_token_type	check_char(char c)
{
	char			*non_char;
	t_token_type	type;
	int				i;

	non_char = "\'\"|><";
	i = 0;
	type = WORD;
	while (non_char[i])
	{
		if (c == non_char[i] || is_wspace(c) == true)
		{
			if (c == non_char[i])
				type = i;
			else
				type = WHITESPACE;
			return (type);
		}
		i++;
	}
	return (type);
}

char	*copy_part(char *input, int start, int len)
{
	char	*value;
	int		i;

	value = malloc(len +1);
	i = 0;
	while (len-- > 0)
	{
		value[i] = input[start];
		i++;
		start++;
	}
	value[i] = '\0';
	return (value);
}

char	**split_string(char *input, int start, int len)
{
	char		*temp;
	char		**words;
	int			i;

	temp = copy_part(input, start, len);
	i = 0;
	while (temp[i])
	{
		if (temp[i] == 9)
			temp[i] = 32;
		i++;
	}
	words = ft_split(temp, 32);
	free(temp);
	return (words);
}

int	get_value_len(char *input, int i, t_token_type type)
{
	int	len;
	int	start;

	len = 0;
	start = i;
	while (input[i])
	{
		if (type < 2 && i != start && check_char(input[i]) == type)
			break ;
		else if (type >= 2 && check_char(input[i]) != type)
			break ;
		len++;
		i++;
	}
	return (len);
}

int	valid_next(t_token *token)
{
	while (token && token->type == WHITESPACE)
		token = token->next;
	if (token == NULL)
		return(false);
	if (token->type != WORD && token->type != SINGLE_QUOTE
		&& token->type != DOUBLE_QUOTE)
		return (false);
	return (true);
}

int	valid_prev(t_token *token)
{
	while (token && token->type == WHITESPACE)
		token = token->prev;
	if (token == NULL)
		return(false);
	if (token->type != WORD && token->type != SINGLE_QUOTE
		&& token->type != DOUBLE_QUOTE)
		return (false);
	return (true);
}

void	check_syntax(t_token **head)
{
	t_token	*ptr;

	if (head == NULL)
		return ;
	ptr = *head;
	while (ptr)
	{
		if (ptr->type > 1 && ptr->type < 7)
		{
			if (valid_next(ptr->next) == false)
			{
				syntax_error(head, ptr->value[0]);
				return ;
			}
			if (ptr->type == PIPE && valid_prev(ptr->prev) == false)
			{
				syntax_error(head, ptr->value[0]);
				return ;
			}
		}
		ptr = ptr->next;
	}
}

/* void	add_to_list(t_token **head, char **words)
{
	int		i;
	char	*value;
	
	if (words[0] == 0)
	{
		free_splits(words);
		//value = NULL;
		return ; //create_list(head, value, WHITESPACE);
	}
	i = 0;
	while(words[i] != 0)
	{
		value = ft_strdup(words[i]);
		create_list(head, value, WORD);
		i++;
	}
	free_splits(words);
} */