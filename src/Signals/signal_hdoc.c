/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:47:54 by lhagemos          #+#    #+#             */
/*   Updated: 2025/02/03 14:13:16 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_interactive(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		g_signal = 128 + sig;
	}
	if (sig == SIGQUIT)
	{
		return ;
	}
}

void	heredoc_noninteractive(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void	set_hdoc_interactive(void)
{
	signal(SIGINT, heredoc_interactive);
	signal(SIGQUIT, heredoc_interactive);
}

void	set_hdoc_noninteractive(void)
{
	signal(SIGINT, heredoc_noninteractive);
	signal(SIGQUIT, heredoc_noninteractive);
}
