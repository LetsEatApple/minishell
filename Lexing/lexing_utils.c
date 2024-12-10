/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:10:19 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/10 14:43:59 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (c == non_char[i])
		{
			type = i;
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

void	check_syntax(t_token **head)
{
	t_token	*ptr;

	if (head == NULL)
		return ;
	ptr = *head;
	while (ptr != NULL)
	{
		if (ptr->type > 1 && ptr->type < 7)
		{
			if (ptr->next == NULL || ptr->next->type != WORD)
			{
				syntax_error(head, ptr->value[0]);
				return ;
			}
			if (ptr->type == PIPE && ptr->prev->type != WORD)
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