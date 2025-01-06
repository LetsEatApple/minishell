/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:19:29 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/20 19:06:19 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	ft_exit(t_data *data, char **cmd)
{
	int	code;
	int	size;

	code = g_signal;
	size = ft_arrlen(cmd);
	if (size > 1 && check_arg(cmd[1]) == false)
	{
		print_error_fd("exit: %s: numeric argument required\n", cmd[1]);
		code = 2;
	}
	if (check_arg(cmd[1]) == true && size > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (size == 2 && check_arg(cmd[1]) == true)
		code = get_code(cmd[1]);
	//printf("code: %d\n", code);
	free_data(data);
	exit(code);
}
