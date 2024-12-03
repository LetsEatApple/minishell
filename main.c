/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:43:17 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/02 19:00:30 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile __sig_atomic_t	g_signal = 0;

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
	if (data->token_list != NULL)
		ft_command(data);
	free_data(data);
}

int main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	g_signal = 0;
	init_data(&data, ac, envp);
	while ("It's been a")
	{
		signal(SIGINT, handle_sig);
		signal(EOF, handle_sig);
		data.input = readline("minihell: ");
		if (data.input == NULL) // EOF (ctrl-D) detected
			break ;
		add_history(data.input);
		if (data.input)
		{
			lexing(&data);
			print_list(&data);
			init_msh(&data);
		}
	}
	/* rl_clear_history();
	free_data(&data); */
	return (g_signal);
}