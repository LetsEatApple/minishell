/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:28:41 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/05 17:26:28 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	add_exp(t_env **head, t_env *new)
{
	t_env	*ptr;

	if (!head || !new)
		return ;
	ptr = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (ptr -> next != NULL)
			ptr = ptr -> next;
		ptr -> next = new;
		new -> prev = ptr;
	}
}

int	split_point(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		i++;
	}
	return (i);
}

char	*getexp(char *s, char *arg)
{
	char	*res;
	int		i;

	i = split_point(s);
	if (strncmp(arg, "var", 3) == 0)
	{
		res = ft_substr(s, 0, i);
		return (res);
	}
	if (s[i] == '\0')
		res = NULL;
	else
		res = ft_substr(s, i +1, ft_strlen(s) - i);
	return (res);
}

t_env	*new_exp(char *var, int exp)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new -> var = getexp(var, "var");
	new -> value = getexp(var, "val");
	new -> exp = exp;
	new -> index = -1;
	new -> next = NULL;
	new -> prev = NULL;
	return (new);
}

void	make_list(t_env **head, char *value, int exp)
{
	t_env	*new;

	new = new_exp(value, exp);
	add_exp(head, new);
}
