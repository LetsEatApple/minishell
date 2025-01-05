/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:27:20 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/05 19:57:38 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	delete_var(t_env **head, t_env	*todelete)
{
	t_env	*ptr;

	if (*head == todelete)
	{
		*head = (*head)->next;
		if ((*head)->prev->value != NULL)
			free((*head)->prev->value);
		if ((*head)->prev->var != NULL)
			free((*head)->prev->var);
		free((*head)->prev);
		(*head)->prev = NULL;
	}
	else if (todelete->next == NULL)
	{
		ptr = todelete->prev;
		if (todelete->value != NULL)
			free(todelete->value);
		if (todelete->var != NULL)
			free(todelete->var);
		free(todelete);
		ptr->next = NULL;
	}
	else
	{
		ptr = todelete->prev;
		ptr->next = todelete->next;
		todelete->next->prev = ptr;
		if (todelete->value != NULL)
			free(todelete->value);
		if (todelete->var != NULL)
			free(todelete->var);
		free(todelete);
		todelete = NULL;
	}
}

void	check_varg(char *arg, t_env *head)
{
	t_env	*ptr;
	int		size;

	size = ft_strlen(arg);
	ptr = head;
	while (ptr != NULL)
	{
		if (ft_strncmp(arg, ptr->var, size) == 0)
		{
			if (ptr->next == NULL)
			{
				delete_var(&head, ptr);
				break ;
			}
			else
			{
				ptr = ptr->next;
				delete_var(&head, ptr->prev);
			}
		}
		else
			ptr = ptr->next;
	}
}

int	ft_unset(t_data *data, char **cmd)
{
	int	size;
	int	i;

	size = ft_arrlen(cmd);
	if (size == 1)
		return (0); //adjust if needed
	if (cmd[1][0] == '-')
	{
		print_error_fd("invalid option: %s\n", cmd[1]);
		return (2); //adjust if needed
	}
	i = 1;
	while (cmd[i])
	{
		check_varg(cmd[i], data->e_list);
		i++;
	}
	free_split(data->env);
	data->env = list2arr(data);
	return (0);
}
