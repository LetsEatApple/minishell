/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:51:08 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/05 17:19:45 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_smaller(char *next, char *min, int ind)
{
	int	i;
	int	size;

	if (ind != -1)
		return (false);
	i = 0;
	if (ft_strlen(next) < ft_strlen(min))
		size = ft_strlen(next);
	else
		size = ft_strlen(min);
	while (i < size)
	{
		if (next[i] == min[i])
			i++;
		else
			break ;
	}
	if (next[i] < min[i])
		return (true);
	return (false);
}

int	check_var(char *s, t_env *head)
{
	t_env	*ptr;
	int		size;

	size = split_point(s);
	ptr = head;
	while (ptr != NULL)
	{
		if (ft_strncmp(s, ptr->var, size) == 0)
			return (true);
		ptr = ptr->next;
	}
	return (false);
}

void	replace_val(char *s, t_env **head)
{
	t_env	*ptr;
	int		size;
	char	*val;

	size = split_point(s);
	val = ft_substr(s, size +1, ft_strlen(s) -size);
	ptr = *head;
	while (ptr)
	{
		if (ft_strncmp(s, ptr->var, size) == 0)
		{
			if (ptr->value != NULL)
				free(ptr->value);
			ptr->value = val;
			ptr->exp = 0;
			break ;
		}
		ptr = ptr->next;
	}
	return ;
}

void	reset_index(t_env **head)
{
	t_env	*ptr;

	ptr = *head;
	while (ptr)
	{
		ptr->index = -1;
		ptr = ptr->next;
	}
}

void	print_exp_var(t_env *ptr)
{
	if (ptr->exp == 1)
		printf("declare -x %s\n", ptr->var);
	else
	{
		if (ptr->value != NULL)
			printf("declare -x %s=\"%s\"\n", ptr->var, ptr->value);
		else
			printf("declare -x %s=\"\"\n", ptr->var);
	}
}
