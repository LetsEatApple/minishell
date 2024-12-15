/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:20:07 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/12 22:47:08 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_arrlen(char **cmd)
{
	int	i;

	i = 0;
	while(cmd[i])
		i++;
	return (i);
}

void	print_echo(char **cmd, int i)
{
	i += 1;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i+1] != 0)
			printf(" ");
		i++;
	}
}

int	ft_echo(char **cmd)
{
	int	i;
	int	n;

	n = 0;
	printf("size: %d\n", ft_arrlen(cmd));
	if (ft_arrlen(cmd) > 1 && ft_strncmp(cmd[1], "-n", 3) == 0)
		n = 1;
	i = n+1;
	while (cmd[i] != NULL)
	{
		if (cmd[i][0] != '\0')
			printf("%s", cmd[i]);
		if (cmd[i+1] != NULL)
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
//}
	
	/* int	n;
	int	size; */

	//print_arr(cmd); 
	/* size = ft_arrlen(cmd);
	if (size == 1)
	{
		printf("\n");
		return (0);
	}
	n = 0;
	if (ft_strncmp(cmd[1], "-n", 3) == 0)
		n = 1;
	if (size == 2 && n == 1)
		return (0);
	print_echo(cmd, n);
	if (n == 0)
		printf("\n"); */
	return (0);
}
// need to add in -n option
/* int	ft_echo(t_data *data)
{
	char	*input;
	char	*input_copy;

	input = NULL;
	if (ft_strlen(data->input) == 4)
	{
		printf("\n");
		return (0);
	}
	input = ft_substr(data->input, 5, ft_strlen(data->input) - 5);
	input_copy = input;
	while (*input)
	{
		if (*input == '$')
		{
			print_env_sing(data, input);
			while (*(input + 1))
			{
				if (*(input + 1) == ' ' || *(input + 1)  == '\t' \
					|| *(input + 1) == '\n' || *input == '\f' \
					|| *input == '\v' || *input == '\r')
					break;
				input++;
			}
		}
		else
			ft_putchar_fd(*input, 1);
		input++;
	}
	free(input_copy);
	printf("\n");
	return (0);
} */

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

int is_whitespace(char c)
{
	if (!c || c == '\0')
		return (1);
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\f' || c == '\v' || c == '\r')
		return (1);
	return (0);
}
