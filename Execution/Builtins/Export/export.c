/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:17:26 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/29 16:22:58 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_export(t_env *e_list)
{
	t_env	*ptr;
	int		size;
	int		i;

	if (e_list == NULL)
		return ;
	i = 0;
	size = lst_size(e_list, 2);
	printf("s: %d\n", size);
	ptr = e_list;
	while (i != size)
	{
		while (ptr)
		{
			if (ptr->index == i)
			{
				print_exp_var(ptr);
				i++;
				break ;
			}
			ptr = ptr->next;
		}
		ptr = e_list;
	}
}

void	sort_env(t_env **e_list)
{
	t_env	*current;
	t_env	*next;
	t_env	*min;
	int		i;

	i = 0;
	current = *e_list;
	while (current)
	{
		min = current;
		next = current->next;
		while (next)
		{
			if (is_smaller(next->var, min->var, next->index) == true)
				min = next;
			next = next->next;
		}
		min->index = i;
		i++;
		current = *e_list;
		while (current && current->index != -1)
			current = current->next;
	}
}

//only if the first arg is an (invalid)option export does not continue
int	check_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (i == 1 && cmd[i][0] == '-')
		{
			error_msg("invalid option: %s\n", cmd[i], 2);
			return (false);
		}
		if (ft_isalpha(cmd[i][0]) == false && cmd[i][0] != '_')
			error_msg("not a valid identifier: %s\n", cmd[i], 1);
		i++;
	}
	return (true);
}

void	process_args(char **cmd, t_data *data)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (check_var(cmd[i], data->e_list) == false)
		{
			if (charnstr(cmd[i], '=') == false)
				make_list(&data->e_list, cmd[i], 1);
			else
				make_list(&data->e_list, cmd[i], 0);
		}
		else
		{
			if (charnstr(cmd[i], '=') == true)
				replace_val(cmd[i], &data->e_list);
		}
		i++;
	}
}

void	ft_export(t_data *data, char **cmd)
{
	int	size;

	g_signal = 0;
	size = ft_arrlen(cmd);
	if (size == 1)
	{
		reset_index(&data->e_list);
		sort_env(&data->e_list);
		print_export(data->e_list);
	}
	else
	{
		if (check_args(cmd) == false)
			return ;
		process_args(cmd, data);
		free_split(data->env);
		data->env = list2arr(data);
	}
}
