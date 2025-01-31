/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:19:29 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/31 21:03:00 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (false);
	while (arg[i] == 32 || arg[i] == 9)
		i++;
	if (arg[i] == 45 || arg[i] == 43)
		i++;
	if (arg[i] == '\0')
		return (false);
	while (arg[i])
	{
		if (arg[i] >= 48 && arg[i] <= 57)
			i++;
		else
			return (false);
	}
	return (true);
}

int	get_code(char *arg)
{
	int	code;

	code = ft_atoi(arg);
	if (code < 0)
	{
		while (code < 0)
			code += 256;
	}
	if (code > 255)
		code %= 256;
	return (code);
}

void	ft_exit(t_data *data, char **cmd)
{
	int	size;

	size = ft_arrlen(cmd);
	if (size > 1 && check_arg(cmd[1]) == false)
		error_msg("exit: %s: numeric argument required\n", cmd[1], 2);
	if (check_arg(cmd[1]) == true && size > 2)
	{
		error_msg("%s: too many arguments\n", cmd[0], 1);
		return ;
	}
	if (size == 2 && check_arg(cmd[1]) == true)
		g_signal = get_code(cmd[1]);
	free_data(data);
	exit(g_signal);
}
