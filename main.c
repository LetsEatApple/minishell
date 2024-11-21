/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:43:17 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/21 16:04:04 by lhagemos         ###   ########.fr       */
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
	if (sig == SIGQUIT)
	{
		printf("sigquit\n");
	}
}

int main(int ac, char **av, char **envp)
{
	char	*line;
	(void)av;
	(void)envp;
	if (ac != 1)
		return (0);
	
	while(1)
	{
		signal(SIGINT, handle_sig);
		signal(EOF, handle_sig);
		line = readline("minihell: ");
		if (line == NULL) // EOF (ctrl-D) detected
			break ;
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return 0;
}