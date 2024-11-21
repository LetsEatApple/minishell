/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:43:17 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/21 13:48:35 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("signal received\n");
		exit (0);
	}
}
int main(int ac, char **av, char **envp)
{
	(void)av;
    (void)envp;
	char *line;
	struct sigaction sa;
	
    if (ac > 1)
		return (0);
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	while(1)
	{
		signal(SIGINT, handle_sigint);
		line = readline("minihell: ");
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return 0;
}