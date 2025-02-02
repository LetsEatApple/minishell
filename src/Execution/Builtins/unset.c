/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:27:20 by lhagemos          #+#    #+#             */
/*   Updated: 2025/02/02 17:00:05 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	free_node(t_env *ptr)
{
	if (ptr->value != NULL)
		free(ptr->value);
	if (ptr->var != NULL)
		free(ptr->var);
	free(ptr);
	ptr = NULL;
}

void	delete_var(t_data *data, t_env **head, t_env	*todelete)
{
	t_env	*ptr;

	if (*head == todelete && todelete->next == NULL)
		clear_elist(data, &data->e_list);
	else if (*head == todelete)
	{
		*head = (*head)->next;
		free_node((*head)->prev);
		(*head)->prev = NULL;
	}
	else if (todelete->next == NULL)
	{
		ptr = todelete->prev;
		free_node(todelete);
		ptr->next = NULL;
	}
	else
	{
		ptr = todelete->prev;
		ptr->next = todelete->next;
		todelete->next->prev = ptr;
		free_node(todelete);
		todelete = NULL;
	}
}

void	check_varg(char *arg, t_data *data)
{
	t_env	*ptr;
	int		size;

	size = ft_strlen(arg);
	ptr = data->e_list;
	while (ptr != NULL)
	{
		if (ft_strncmp(arg, ptr->var, size) == 0)
		{
			if (ptr->next == NULL)
			{
				delete_var(data, &data->e_list, ptr);
				break ;
			}
			else
			{
				ptr = ptr->next;
				delete_var(data, &data->e_list, ptr->prev);
			}
		}
		else
			ptr = ptr->next;
	}
}

void	ft_unset(t_data *data, char **cmd)
{
	int	size;
	int	i;

	g_signal = 0;
	size = ft_arrlen(cmd);
	if (size == 1)
		return ;
	if (cmd[1][0] == '-')
	{
		error_msg("invalid option: %s\n", cmd[1], 2);
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		check_varg(cmd[i], data);
		i++;
	}
	free_split(data->env);
	data->env = list2arr(data);
}
