/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:43:17 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/21 14:56:19 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == EOF)
	{
		printf("ctrl + d\n");
		//rl_clear_history();
		//exit (0);
	}
}

int main(int ac, char **av, char **envp)
{
	char	*line;
	struct	sigaction sa;
	(void)av;
	(void)envp;
	if (ac > 1)
		return (0);
	sa.sa_handler = &handle_sig;
	sa.sa_flags = 0;
	
	
	while(1)
	{
		signal(SIGINT, handle_sig);
		signal(EOF, handle_sig);
		line = readline("minihell: ");
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return 0;
}