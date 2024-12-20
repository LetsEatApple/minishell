/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:20:07 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/20 12:06:20 by lhagemos         ###   ########.fr       */
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
		print_err("invalid option: %s\n", cmd[1]);
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
