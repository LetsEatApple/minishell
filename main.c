/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:43:17 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/26 16:55:20 by lhagemos         ###   ########.fr       */
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

void	init_msh(t_data *data)
{
	ft_command(data);
}

int main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	(void)envp;
	init_data(&data, ac, envp);
	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(EOF, handle_sig);
		data.input = readline("minihell: ");
		if (data.input == NULL) // EOF (ctrl-D) detected
			break ;
		add_history(data.input);
		if (data.input)
		{
			lexing(data.input); // return or change?
			//init_msh(&data);
			free(data.input);
		}
	}
	rl_clear_history();
	free_data(&data);
	return 0;
}