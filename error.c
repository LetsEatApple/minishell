/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:15:00 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/19 12:19:30 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(t_token **head, char c)
{
	printf("syntax error near unexpected token '%c'\n", c);
	clearlist(head);
	*head = NULL;
}

void	print_error_fd(const char *error, char *target)
{
	int		i;

	i = 0;
	while (error[i])
	{
		if (error[i] == '%')
		{
			i++;
			ft_putstr_fd(target, 2);
		}
		else
			ft_putchar_fd(error[i], 2);
		i++;
	}
}

void	printf_error(char *str, int signal)
{
	printf("%s\n", str);
	g_signal = signal;
}