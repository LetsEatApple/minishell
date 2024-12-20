/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:20:07 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/20 17:07:43 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_arrlen(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	n;

	n = 0;
	if (ft_arrlen(cmd) > 1 && ft_strncmp(cmd[1], "-n", 3) == 0)
		n = 1;
	i = n +1;
	while (cmd[i] != NULL)
	{
		if (cmd[i][0] != '\0')
			printf("%s", cmd[i]);
		if (cmd[i +1] != NULL)
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	return (0);
}

int	ft_pwd(char **cmd, char** env)
{
	int		i;
	int		size;
	char	*pwd;

	if (ft_arrlen(cmd) != 1 && cmd[1][0] == '-')
	{
		print_error_fd("invalid option: %s\n", cmd[1]);
		return (2);
	}
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
	{
		printf("no var\n"); //adjust
		return (0); //adjust
	}
	size = ft_strlen(env[i]) - 4;
	pwd = ft_substr(env[i], 4, size);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

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
		if (arg[i] < 48 && arg[i] > 57)
			return (false);
		i++;
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
	printf("code: %d\n", code);
	free_data(data);
	exit(code);
}
//e.g.: exit 1 32 / exit 1 not > bash: exit: too many arguments > not executing (only if just numeric arg)
	//e.g.: exit not / exit not 2 > exit: 'arg_name': numeric argument required > still executing with 2

int	get_key_len(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	is_whitespace(char c)
{
	if (!c || c == '\0')
		return (1);
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\f' || c == '\v' || c == '\r')
		return (1);
	return (0);
}
