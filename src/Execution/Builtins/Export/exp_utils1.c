/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:29:55 by lhagemos          #+#    #+#             */
/*   Updated: 2025/02/02 15:57:43 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	lst_size(t_env *head, int i)
{
	int		size;
	t_env	*ptr;

	if (!head)
		return (0);
	size = 0;
	ptr = head;
	while (ptr)
	{
		if (ptr->exp != i)
			size++;
		ptr = ptr->next;
	}
	return (size);
}

t_env	*arr2list(t_data *data)
{
	int		i;
	t_env	*head;

	i = 0;
	if (data->env == NULL)
		return (NULL);
	head = NULL;
	while (data->env[i])
	{
		make_list(&head, data->env[i], 0);
		i++;
	}
	return (head);
}

char	*get_env_var(t_env *ptr)
{
	char	*temp;
	char	*env;

	temp = ft_strjoin(ptr->var, "=");
	if (ptr->value != NULL)
		env = ft_strjoin(temp, ptr->value);
	else
		env = ft_strdup(temp);
	free(temp);
	return (env);
}

char	**list2arr(t_data *data)
{
	int		len;
	char	**env;
	t_env	*ptr;
	int		i;

	if (data->e_list == NULL)
		return (NULL);
	i = 0;
	len = lst_size(data->e_list, 1);
	env = malloc((len +1) * sizeof(char *));
	ptr = data->e_list;
	while (ptr)
	{
		if (ptr->exp == 0)
		{
			env[i] = get_env_var(ptr);
			i++;
		}
		ptr = ptr->next;
	}
	env[i] = 0;
	return (env);
}

int	charnstr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (true);
		i++;
	}
	return (false);
}

/* void	print_elist(t_env *head)
{
	t_env	*ptr;

	ptr = head;
	while(ptr)
	{
		printf("var= %s, ind= %d, exp= %d\n", ptr->var, ptr->index, ptr->exp);
		ptr = ptr->next;
	}
} */
