/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:15:00 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/29 08:28:47 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(t_token **head, char c)
{
	printf("syntax error near unexpected token '%c'\n", c);
	clearlist(head);
	*head = NULL;
	g_signal = 2;
}

void	print_error_fd(const char *error, char *target, int sig)
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
	g_signal = sig;
}

void	ft_perror(char *str, int signal)
{
	perror(str);
	g_signal = signal;
}
